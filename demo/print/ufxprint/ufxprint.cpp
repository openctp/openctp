#include <iostream>
#include <mutex>
#include <condition_variable>
#include "UFX/tool.h"
#include "UFX/t2sdk_interface.h"

#define  MSGCENTER_FUNC_HEART		 620000                                           //消息中心心跳功能号
#define  MSGCENTER_FUNC_REG			 620001                                           //消息中心订阅功能号
#define  MSGCENTER_FUNC_REG_CANCLE   620002                                           //消息中心取消订阅功能号
#define  MSGCENTER_FUNC_SENDED		 620003                                           //消息中心主推功能号
#define ISSUE_TYPE_REALTIME_SECU     12                                               //订阅证券成交回报
#define ISSUE_TYPE_ENTR_BACK         23                                               //订阅委托回报


class semaphore
{
public:
    semaphore(int value = 1) :count(value) {}

    void wait()
    {
        unique_lock<mutex> lck(mt);
        if (--count < 0)//资源不足挂起线程
            cv.wait(lck);
    }

    void signal()
    {
        unique_lock<mutex> lck(mt);
        if (++count <= 0)//有线程挂起，唤醒一个
            cv.notify_one();
    }

private:
    int count;
    mutex mt;
    condition_variable cv;
};

semaphore _semaphore(0);

// 自定义类CCallback，通过继承（实现）CCallbackInterface，来自定义各种事件（包括连接成功、
// 连接断开、发送完成、收到数据等）发生时的回调方法
class CCallback : public CCallbackInterface
{
public:
    CCallback()
    {
        lpConfig = NULL;
        lpConnection = NULL;
//        callback.SetRequestMode(this);
        lpConfig = NewConfig();
        lpConfig->AddRef();
        memset(m_opUserToken,0,sizeof(m_opUserToken));
        m_BranchNo=0;
        memset(m_client_id,0,sizeof(m_client_id));
        iSystemNo=0;
        m_op_branch_no=0;
        memset(m_AccountName,0,sizeof(m_AccountName));
        memset(m_Password,0,sizeof(m_Password));
        memset(pout,0,sizeof(pout));
        m_EntrustWay='\0';
        m_FuturesAccount="0";
        m_opStation="0";
    }

    ~CCallback()
    {
        lpConnection->Release();
        lpConfig->Release();
    }

    // 因为CCallbackInterface的最终纯虚基类是IKnown，所以需要实现一下这3个方法
    unsigned long  FUNCTION_CALL_MODE QueryInterface(const char *iid, IKnown **ppv)
    {
        return 0;
    }
    unsigned long  FUNCTION_CALL_MODE AddRef()
    {
        return 0;
    }

    unsigned long  FUNCTION_CALL_MODE Release()
    {
        return 0;
    }

    // 各种事件发生时的回调方法，实际使用时可以根据需要来选择实现，对于不需要的事件回调方法，可直接return
    // Reserved?为保留方法，为以后扩展做准备，实现时可直接return或return 0。
    void FUNCTION_CALL_MODE OnConnect(CConnectionInterface *lpConnection)
    {
        puts("CCallback::OnConnect");
    }

    void FUNCTION_CALL_MODE OnSafeConnect(CConnectionInterface *lpConnection)
    {
        puts("CCallback::OnSafeConnect");
    }

    void FUNCTION_CALL_MODE OnRegister(CConnectionInterface *lpConnection)
    {
        puts("CCallback::OnRegister");
    }

    // 断开连接后会调用Onclose函数，提示连接断开
    void FUNCTION_CALL_MODE OnClose(CConnectionInterface *lpConnection)
    {
        puts("CCallback::OnClose");
    }

    void FUNCTION_CALL_MODE OnSent(CConnectionInterface *lpConnection, int hSend, void *reserved1, void *reserved2, int nQueuingData)
    {
        puts("CCallback::OnSent");
    }

    void FUNCTION_CALL_MODE Reserved1(void *a, void *b, void *c, void *d)
    {
        puts("CCallback::Reserved1");
    }
    void FUNCTION_CALL_MODE Reserved2(void *a, void *b, void *c, void *d)
    {
        puts("CCallback::Reserved2");
    }
    int  FUNCTION_CALL_MODE Reserved3()
    {
        return 0;
    }
    void FUNCTION_CALL_MODE Reserved4() {}
    void FUNCTION_CALL_MODE Reserved5() {}
    void FUNCTION_CALL_MODE Reserved6() {}
    void FUNCTION_CALL_MODE Reserved7() {}

    void FUNCTION_CALL_MODE OnReceivedBiz(CConnectionInterface *lpConnection, int hSend, const void *lpUnPackerOrStr, int nResult) {}
    void FUNCTION_CALL_MODE OnReceivedBizEx(CConnectionInterface *lpConnection, int hSend, LPRET_DATA lpRetData, const void *lpUnpackerOrStr, int nResult)
    {
        puts("CCallback::OnReceivedBizEx");
    }

    // 异步接受调用函数，用于异步发送包请求后，线程接受返回包
    void FUNCTION_CALL_MODE OnReceivedBizMsg(CConnectionInterface *lpConnection, int hSend, IBizMessage* lpMsg)
    {
        puts("CCallback::OnReceivedBizMsg");
        if (lpMsg!=NULL)
        {
            // 成功,应用程序不能释放lpBizMessageRecv消息
            if (lpMsg->GetReturnCode() ==0)
            {
                // 如果要把消息放到其他线程处理，必须自行拷贝，操作如下：
                // int iMsgLen = 0;
                // void * lpMsgBuffer = lpBizMessageRecv->GetBuff(iMsgLen);
                // 将lpMsgBuffer拷贝走，然后在其他线程中恢复成消息可进行如下操作：
                // lpBizMessageRecv->SetBuff(lpMsgBuffer,iMsgLen);
                // 没有错误信息
                int iLen = 0;
                const void * lpBuffer = lpMsg->GetContent(iLen);
                IF2UnPacker * lpUnPacker = NewUnPacker((void *)lpBuffer,iLen);
                switch(lpMsg->GetFunction())
                {
                    case 331100:
                        if (lpUnPacker){
                            lpUnPacker->AddRef();
                            ShowPacket(lpUnPacker);
                            OnResponse_331100(lpUnPacker);
                            lpUnPacker->Release();
                            _semaphore.signal();
                        }
                        break;
                    case 333104:
                        if (lpUnPacker){
                            lpUnPacker->AddRef();
                            OnResponse_333104(lpUnPacker);
                            lpUnPacker->Release();
                        }
                        break;
                    case MSGCENTER_FUNC_HEART:
                    {
                        if (lpMsg->GetPacketType() == REQUEST_PACKET)
                            cout << "heartBeat.." << endl;
                        OnHeartbeat(lpMsg);
                        break;
                    }
                    case MSGCENTER_FUNC_REG:
                    {
                        int iLen_ley = 0;
                        const void * lpBuffer_key = lpMsg->GetKeyInfo(iLen_ley);
                        IF2UnPacker * lpUnPacker_key = NewUnPacker((void *)lpBuffer_key, iLen_ley);
                        if (lpUnPacker_key){
                            lpUnPacker_key->AddRef();
                            if (lpUnPacker_key->GetInt("error_no") != 0){
                                puts(lpUnPacker_key->GetStr("error_info"));
                                lpUnPacker_key->Release();
                            } else {
                                if (lpMsg->GetIssueType() == ISSUE_TYPE_REALTIME_SECU) {
                                    puts("订阅成交主推成功...");
                                } else if (lpMsg->GetIssueType() == ISSUE_TYPE_ENTR_BACK) {
                                    puts("订阅证券委托主推成功...");
                                } else {
                                    puts("订阅成功...");
                                }
                                ShowPacket(lpUnPacker_key);
                                lpUnPacker_key->Release();
                            }
                        }
                        _semaphore.signal();
                        break;
                    }
                    case MSGCENTER_FUNC_REG_CANCLE:
                    {
                        int iLen_ley = 0;
                        const void * lpBuffer_key = lpMsg->GetKeyInfo(iLen_ley);
                        IF2UnPacker * lpUnPacker_key = NewUnPacker((void *)lpBuffer_key, iLen_ley);
                        if (lpUnPacker_key){
                            lpUnPacker_key->AddRef();
                            if (lpUnPacker_key->GetInt("error_no") != 0){
                                puts(lpUnPacker_key->GetStr("error_info"));
                                lpUnPacker_key->Release();
                            } else {
                                if (lpMsg->GetIssueType() == ISSUE_TYPE_REALTIME_SECU) {
                                    puts("取消订阅成交主推成功...");
                                } else if (lpMsg->GetIssueType() == ISSUE_TYPE_ENTR_BACK) {
                                    puts("取消订阅证券委托主推成功...");
                                } else {
                                    puts("取消订阅成功...");
                                }
                                ShowPacket(lpUnPacker_key);
                                lpUnPacker_key->Release();
                            }
                        }
                        _semaphore.signal();
                        break;
                    }
                    case MSGCENTER_FUNC_SENDED:
                    {
                        int iLen_ley = 0;
                        const void * lpBuffer_key = lpMsg->GetKeyInfo(iLen_ley);
                        IF2UnPacker * lpUnPacker_key = NewUnPacker((void *)lpBuffer_key, iLen_ley);
                        if (lpUnPacker_key) {
                            lpUnPacker_key->AddRef();
                            if (lpMsg->GetIssueType() == ISSUE_TYPE_REALTIME_SECU) {
                                printf("该信息为证券成交主推信息！\n");
                                ShowPacket(lpUnPacker_key);
                                lpUnPacker_key->Release();
                            }
                            if (lpMsg->GetIssueType() == ISSUE_TYPE_ENTR_BACK) {
                                printf("该信息为证券委托主推信息！\n");
                                ShowPacket(lpUnPacker_key);
                                lpUnPacker_key->Release();
                            }
                        }
                        break;
                    }
                    default:
                        if (lpUnPacker){
                            lpUnPacker->AddRef();
                            ShowPacket(lpUnPacker);
                            lpUnPacker->Release();
                            _semaphore.signal();
                        }
                        break;
                }
            }
            else
            {
                int iLen = 0;
                const void * lpBuffer = lpMsg->GetContent(iLen);
                IF2UnPacker * lpUnPacker = NewUnPacker((void *)lpBuffer, iLen);
                if (lpUnPacker != NULL)
                {
                    lpUnPacker->AddRef();//添加释放内存引用
                    ShowPacket(lpUnPacker);
                    lpUnPacker->Release();
                }
                else
                {
                    printf("业务包是空包，错误代码：%d，错误信息:%s\n", lpMsg->GetErrorNo(), lpMsg->GetErrorInfo());
                }
                _semaphore.signal();
            }
        }
    }
    //int FUNCTION_CALL_MODE EncodeEx(const char *pIn, char *pOut);
public:
    char m_opUserToken[512];
    int m_BranchNo;
    char m_client_id[18];
    int iSystemNo;
    int m_op_branch_no;

    //维护心跳
    void OnHeartbeat(IBizMessage* lpMsg)
    {
        lpMsg->ChangeReq2AnsMessage();
        lpConnection->SendBizMsg(lpMsg, 1);
    return;
    }

    // 331100 登入响应
    void OnResponse_331100(IF2UnPacker *lpUnPacker)
    {
        int iSystemNo=-1;
        puts("CCallback::331100 登入异步应答");
        const char *pClientId = lpUnPacker->GetStr("client_id");
        if(pClientId)
        {
            strcpy(m_client_id, pClientId);
        }
        cout << "clientId:" << m_client_id << endl;
        if(lpUnPacker->GetStr("user_token") != NULL)
        {
            strcpy(m_opUserToken , lpUnPacker->GetStr("user_token"));
        }
        cout<<"UserToken:" << m_opUserToken <<endl;
        if(lpUnPacker->GetStr("branch_no") != NULL)
        {
            m_BranchNo = lpUnPacker->GetInt("branch_no");
        }
        iSystemNo = lpUnPacker->GetInt("sysnode_id");
        cout<<"iSystemNo:" << iSystemNo <<endl;
        if (lpUnPacker->GetInt("op_branch_no")!=NULL)
        {
            m_op_branch_no=lpUnPacker->GetInt("op_branch_no");
        }
        cout<<"op_branch_no:" << m_op_branch_no <<endl;
        return;
    }

    // 333104 证券持仓分页查询
    void OnResponse_333104(IF2UnPacker *lpUnPacker)
    {
        puts("CCallback::333104 证券持仓分页");
        if (lpUnPacker->GetInt("error_no") != 0)
        {
            cout<< lpUnPacker->GetStr("error_info") <<endl;
            return;
        }
        else
        {
            // 取解包数据记录条数
            int ct = lpUnPacker->GetRowCount();
            string pos = "";
            // 判断是否为结尾
            while (!lpUnPacker->IsEOF())
            {
                // 获取最后一条数据的position_str，作为下一个请求包中position_str的输入参数。如此反复
                const char* lpStrPos = lpUnPacker->GetStr("position_str");
                if (lpStrPos == 0)
                    pos = "";
                else
                    pos = lpStrPos;
                // 取下一条记录
                lpUnPacker->Next();
            }

            if (pos.length() != 0)
            {
                ShowPacket(lpUnPacker);
                ReqFunction333104(pos.c_str());
            }
            else
            {
                puts("CCallback::333104 证券持仓分页查询结束");
                _semaphore.signal();
            }
        }
        return;
    }

    int InitConn()
    {
        if (lpConfig->Load("t2sdk.ini") != 0) {
            cerr << "lpConfig load t2sdk.ini fail" << endl;
            return -1;
        }
        const char *p_fund_account = lpConfig->GetString("ufx", "fund_account", "");
        const char *p_password = lpConfig->GetString("ufx", "password", "");
        strcpy(m_AccountName,p_fund_account);
        strcpy(m_Password,p_password);
//        m_EntrustWay='7';
        lpConfig->SetString("ufx", "fund_account", p_fund_account);
        lpConfig->SetString("ufx", "password", p_password);


        const char *p_serverAddr = lpConfig->GetString("t2sdk", "servers", "");
        const char *p_license_file = lpConfig->GetString("t2sdk", "license_file", "");
        const char *p_license_pwd = lpConfig->GetString("t2sdk", "license_pwd", "");
        const char *p_login_name = lpConfig->GetString("t2sdk", "login_name", "");

        // 配置连接对象
        lpConfig->SetString("t2sdk", "servers", p_serverAddr);
        cout<<"start checking license"<<endl;
        lpConfig->SetString("t2sdk", "license_file", p_license_file);
        lpConfig->SetString("t2sdk", "license_pwd", p_license_pwd);
        cout<<"start loading clientname"<<endl;
        lpConfig->SetString("t2sdk", "login_name", p_login_name);
        cout<<"Connect Successful"<<endl;

        //如果接入ar设置了safe_level，则需要做以下代码
        // none（明文）:只需要修改safe_ssl=none，即可其他默认
        lpConfig->SetString("safe", "safe_level", "none");
        //lpConfig->SetString("safe", "cert_file", "c20121011.pfx");
        //lpConfig->SetString("safe", "cert_pwd", "111111");

        m_EntrustWay='7';
        int iRet = 0;
        if(lpConnection != NULL)
        {
            lpConnection->Release();
            lpConnection = NULL;
        }

        lpConnection = NewConnection(lpConfig);
        cout<< "Connected successfully" <<endl;
        lpConnection->AddRef();
        if (0 != (iRet = lpConnection->Create2BizMsg(this)))
        {
            cerr<<"初始化失败.iRet="<<iRet<<" msg:"<<lpConnection->GetErrorMsg(iRet)<<endl;
            return -1;
        }
        if (0 != (iRet = lpConnection->Connect(3000)))
        {
            cerr<<"连接.iRet="<<iRet<<" msg:"<<lpConnection->GetErrorMsg(iRet)<<endl;
            return -1;
        }

        // 331100 登入
        ReqFunction331100();

        return 0;
    }

    // 331100 证券客户登陆
    int ReqFunction331100()
    {
        int iRet=0,hSend=0, iLen=0;
        // 密码加密
        // cout<<"password"<<m_Password<<endl;
        //EncodeEx(m_Password,pout);
        //cout<<"pout: "<<pout<<endl;
        cout<<"331100客户登陆入参如下："<<endl;
        IBizMessage* lpBizMessage=NewBizMessage();
        lpBizMessage->AddRef();
        lpBizMessage->SetFunction(331100);
        lpBizMessage->SetSubSystemNo(1000);
        lpBizMessage->SetCompanyID(91000);
        lpBizMessage->SetPacketType(REQUEST_PACKET);

        IF2Packer *pPacker=NewPacker(2);
        if (!pPacker)
        {
            printf("取打包器失败！\r\n");
            return -1;
        }
        pPacker->AddRef();
        pPacker->BeginPack();
        ///加入字段名
        pPacker->AddField("op_branch_no", 'I', 5);//操作分支机构
        pPacker->AddField("op_entrust_way", 'C', 1);//委托方式
        pPacker->AddField("op_station", 'S', 255);//站点地址
        pPacker->AddField("branch_no", 'I', 5);
        pPacker->AddField("input_content", 'C');
        pPacker->AddField("account_content", 'S', 30);
        pPacker->AddField("content_type",'S', 6);
        pPacker->AddField("password",'S', 10);
        pPacker->AddField("password_type", 'C');
        //pPacker->AddField("asset_prop",'C');
        ///加入对应的字段值
        pPacker->AddInt(0);
        pPacker->AddChar(m_EntrustWay);
        pPacker->AddStr(m_opStation.c_str());
        pPacker->AddInt(22);
        pPacker->AddChar('1');
        pPacker->AddStr(m_AccountName);
        pPacker->AddStr("0");
        pPacker->AddStr(m_Password);
        //pPacker->AddStr(pout);
        pPacker->AddChar('1');
        //pPacker->AddChar('0');
        ///结束打包
        pPacker->EndPack();

        lpBizMessage->SetContent(pPacker->GetPackBuf(),pPacker->GetPackLen());

        //打印入参信息
        IF2UnPacker * in_lpUnPacker = NewUnPacker(pPacker->GetPackBuf(),pPacker->GetPackLen());
        in_lpUnPacker->AddRef();
        ShowPacket(in_lpUnPacker);
        in_lpUnPacker->Release();

        //异步模式登陆
//        lpConnection->SendBizMsg(lpBizMessage, 1);
//        pPacker->FreeMem(pPacker->GetPackBuf());

        /// 同步模式登陆
        hSend=lpConnection->SendBizMsg(lpBizMessage, 0);
        IBizMessage* lpBizMessageRecv = NULL;
        iRet = lpConnection->RecvBizMsg(hSend, &lpBizMessageRecv, 5000);
        const void * lpBuffer = lpBizMessageRecv->GetContent(iLen);
        IF2UnPacker * lpUnPacker = NewUnPacker((void *)lpBuffer,iLen);
        ShowPacket(lpUnPacker);

        // 获取出参
        const char *pClientId = lpUnPacker->GetStr("client_id");
        if(pClientId)
            strcpy(m_client_id, pClientId);
        cout << "clientId:" << m_client_id << endl;
        if(lpUnPacker->GetStr("user_token") != NULL)
        {
            strcpy(m_opUserToken , lpUnPacker->GetStr("user_token"));
        }
        cout << "UserToken:" << m_opUserToken << endl;
        if(lpUnPacker->GetStr("branch_no") != NULL)
        {
            m_BranchNo = lpUnPacker->GetInt("branch_no");
        }
        cout << "BranchNo:" << lpUnPacker->GetStr("branch_no") << endl;
        iSystemNo = lpUnPacker->GetInt("sysnode_id");
        cout << "iSystemNo:" << iSystemNo << endl;
        if (lpUnPacker->GetInt("op_branch_no")!=NULL)
        {
            m_op_branch_no=lpUnPacker->GetInt("op_branch_no");
        }
        cout <<"op_branch_no:" << m_op_branch_no << endl;
        lpUnPacker->Release();
        pPacker->FreeMem(pPacker->GetPackBuf());
        /// 同步模式登陆

        pPacker->Release();
        lpBizMessage->Release();
        return 0;
    }

    //400 证券行情查询
    int ReqFunction400(char* exchange_type, char* stock_code)
    {
        cout<<"400证券行情查询入参:"<<endl;
        IBizMessage* lpBizMessage=NewBizMessage();
        lpBizMessage->AddRef();
        lpBizMessage->SetFunction(400);
        lpBizMessage->SetPacketType(REQUEST_PACKET);
        lpBizMessage->SetSystemNo(iSystemNo);

        IF2Packer *pPacker=NewPacker(2);
        if (!pPacker)
        {
            printf("取打包器失败！\r\n");
            return -1;
        }
        pPacker->AddRef();
        pPacker->BeginPack();
        //加入字段名
        pPacker->AddField("exchange_type",'S');
        pPacker->AddField("stock_code",'S');
        //加入字段值
        pPacker->AddStr(exchange_type);
        pPacker->AddStr(stock_code);
        pPacker->EndPack();

        lpBizMessage->SetContent(pPacker->GetPackBuf(),pPacker->GetPackLen());
        //打印入参信息
        IF2UnPacker * lpUnPacker = NewUnPacker(pPacker->GetPackBuf(),pPacker->GetPackLen());
        lpUnPacker->AddRef();
        ShowPacket(lpUnPacker);
        lpUnPacker->Release();

        lpConnection->SendBizMsg(lpBizMessage, 1);

        pPacker->FreeMem(pPacker->GetPackBuf());
        pPacker->Release();
        lpBizMessage->Release();
        return 0;
    }

    //333002 普通委托
    int ReqFunction333002(char* exchange_type,char* stock_code, double entrust_amount,double entrust_price,char entrust_bs,char* entrust_prop)
    {
        cout<<"333002委托入参如下"<<endl;
        int iRet = 0, hSend = 0;
        ///获取版本为2类型的pack打包器
        IF2Packer *pPacker = NewPacker(2);
        if(!pPacker)
        {
            printf("取打包器失败!\r\n");
            return -1;
        }
        pPacker->AddRef();

        ///定义解包器
        //IF2UnPacker *pUnPacker = NULL;

        IBizMessage* lpBizMessage = NewBizMessage();
        lpBizMessage->AddRef();
        ///应答业务消息
        IBizMessage* lpBizMessageRecv = NULL;
        //功能号
        lpBizMessage->SetFunction(333002);
        lpBizMessage->SetSubSystemNo(1000);
        lpBizMessage->SetCompanyID(91000);
        //请求类型
        lpBizMessage->SetPacketType(REQUEST_PACKET);
        //lpBizMessage->SetSystemNo(iSystemNo);
        ///其他的应答信息
        LPRET_DATA pRetData = NULL;
        ///开始打包
        pPacker->BeginPack();
        ///加入字段名
        pPacker->AddField("op_branch_no", 'I', 5);//名字 类型 长度
        pPacker->AddField("op_entrust_way", 'C', 1);
        pPacker->AddField("op_station", 'S', 255);
        pPacker->AddField("branch_no", 'I', 5);
        pPacker->AddField("client_id", 'S', 18);//客户ID
        pPacker->AddField("fund_account", 'S', 18);//资金账号
        pPacker->AddField("password", 'S', 10);
        pPacker->AddField("password_type", 'C', 1);
        pPacker->AddField("user_token", 'S', 64);
        pPacker->AddField("exchange_type", 'S', 4);
        pPacker->AddField("stock_account", 'S', 15);
        pPacker->AddField("stock_code", 'S', 6);
        pPacker->AddField("entrust_amount", 'F', 19, 2);
        pPacker->AddField("entrust_price", 'F', 18, 3);
        pPacker->AddField("entrust_bs", 'C', 1);
        pPacker->AddField("entrust_prop", 'S', 3);
        pPacker->AddField("batch_no", 'I', 8);
        ///加入对应的字段值
        pPacker->AddInt(m_op_branch_no);
        pPacker->AddChar(m_EntrustWay);
        pPacker->AddStr(m_opStation.c_str());
        pPacker->AddInt(m_BranchNo);
        pPacker->AddStr(m_client_id);
        pPacker->AddStr(m_AccountName);
        pPacker->AddStr(m_Password);
        pPacker->AddChar('2');
        pPacker->AddStr(m_opUserToken);
        pPacker->AddStr(exchange_type);
        pPacker->AddStr("");
        pPacker->AddStr(stock_code);
        pPacker->AddDouble(entrust_amount);
        pPacker->AddDouble(entrust_price);
        pPacker->AddChar(entrust_bs);
        pPacker->AddStr(entrust_prop);
        pPacker->AddInt(13);
        pPacker->EndPack();

        lpBizMessage->SetContent(pPacker->GetPackBuf(),pPacker->GetPackLen());
        //打印入参信息
        IF2UnPacker * lpUnPacker = NewUnPacker(pPacker->GetPackBuf(),pPacker->GetPackLen());
        lpUnPacker->AddRef();
        ShowPacket(lpUnPacker);
        lpUnPacker->Release();

        lpConnection->SendBizMsg(lpBizMessage, 1);
        pPacker->FreeMem(pPacker->GetPackBuf());
        pPacker->Release();
        lpBizMessage->Release();
        return 0;
    }

    //333104 证券持仓查询
    int ReqFunction333104(const char* position_str)
    {
        cout<<"333104 证券持仓查询入参:"<<endl;
        IBizMessage* lpBizMessage = NewBizMessage();
        lpBizMessage->AddRef();
        IBizMessage* lpBizMessageRecv = NULL;
        // 功能号
        lpBizMessage->SetFunction(333104);
        lpBizMessage->SetSubSystemNo(1000);
        lpBizMessage->SetCompanyID(91000);
        //请求类型
        lpBizMessage->SetPacketType(REQUEST_PACKET);
        //设置系统号
        lpBizMessage->SetSystemNo(iSystemNo);

        ///获取版本为2类型的pack打包器
        IF2Packer *pPacker = NewPacker(2);
        if(!pPacker)
        {
            printf("取打包器失败!\r\n");
            return -1;
        }
        pPacker->AddRef();
        ///开始打包
        pPacker->BeginPack();
        ///加入字段名
        pPacker->AddField("op_branch_no", 'I', 5);
        pPacker->AddField("op_entrust_way", 'C', 1);
        pPacker->AddField("op_station", 'S', 255);
        pPacker->AddField("branch_no", 'I', 5);
        pPacker->AddField("client_id", 'S', 18);
        pPacker->AddField("fund_account", 'S', 18);
        pPacker->AddField("password", 'S', 10);
        pPacker->AddField("password_type", 'C', 1);
        pPacker->AddField("user_token", 'S', 512);
        pPacker->AddField("position_str",'S',100);
        pPacker->AddField("request_num",'I',10);
        ///加入对应的字段值
        pPacker->AddInt(0); // op_branch_no
        pPacker->AddChar('7'); //	op_entrust_way
        pPacker->AddStr("hs"); // op_station
        pPacker->AddInt(m_BranchNo); // branch_no
        pPacker->AddStr(m_client_id); // client_id
        pPacker->AddStr(m_AccountName);	// fund_account
        pPacker->AddStr(m_Password); // password
        pPacker->AddChar('1'); // password_type
        pPacker->AddStr(m_opUserToken);	// user_token
        pPacker->AddStr( position_str); // position_str 数据的定位串
        pPacker->AddInt(3); // request_num 请求数;默认50，最大100
        ///结束打包
        pPacker->EndPack();

        lpBizMessage->SetContent(pPacker->GetPackBuf(),pPacker->GetPackLen());
        lpConnection->SendBizMsg(lpBizMessage, 1);
        pPacker->FreeMem(pPacker->GetPackBuf());
        pPacker->Release();
        lpBizMessage->Release();
    }

    // 331300 证券股东信息查询
    int ReqFunction331300()
    {
        cout<<"331300 证券股东信息查询:"<<endl;
        cout<<"isysnum:"<<iSystemNo<<endl;
        cout<<"password:"<<m_Password<<endl;
        cout<<"fund_account:"<<m_AccountName<<endl;
        cout<<"m_opUserToken:"<<m_opUserToken<<endl;
        int hSend = 0;

        IBizMessage* lpBizMessage = NewBizMessage();
        lpBizMessage->AddRef();
        IBizMessage* lpBizMessageRecv = NULL;

        //功能号
        lpBizMessage->SetFunction(331300);
        lpBizMessage->SetSubSystemNo(1000);
        lpBizMessage->SetCompanyID(91000);
        //请求类型
        lpBizMessage->SetPacketType(REQUEST_PACKET);
        //设置营业部号
        //设置系统号
        lpBizMessage->SetSystemNo(iSystemNo);

        ///获取版本为2类型的pack打包器
        IF2Packer *pPacker = NewPacker(2);
        if(!pPacker)
        {
            printf("取打包器失败!\r\n");
            return -1;
        }
        pPacker->AddRef();
        ///开始打包
        pPacker->BeginPack();
        ///加入字段名
        pPacker->AddField("op_branch_no", 'I', 5);//名字 类型 长度
        pPacker->AddField("op_entrust_way", 'C', 1);
        pPacker->AddField("op_station", 'S', 255);
        pPacker->AddField("branch_no", 'I', 5);
        pPacker->AddField("client_id", 'S', 18);
        pPacker->AddField("fund_account", 'S', 18);
        pPacker->AddField("password", 'S', 10);
        pPacker->AddField("password_type", 'C', 1);
        pPacker->AddField("user_token", 'S', 512);
        pPacker->AddField("exchange_type", 'S', 4);
        ///加入对应的字段值
        pPacker->AddInt(0);			//op_branch_no
        pPacker->AddChar('7');			//	op_entrust_way
        pPacker->AddStr("hs");	//op_station
        pPacker->AddInt(m_BranchNo);		//	branch_no
        pPacker->AddStr(m_client_id);	//		client_id
        pPacker->AddStr(m_AccountName);	//	fund_account
        pPacker->AddStr(m_Password);		//password
        pPacker->AddChar('1');			//	password_type
        pPacker->AddStr(m_opUserToken);	//	user_token
        pPacker->AddStr("1");			//exchange_type
        ///结束打包
        pPacker->EndPack();

        lpBizMessage->SetContent(pPacker->GetPackBuf(),pPacker->GetPackLen());
        lpConnection->SendBizMsg(lpBizMessage, 1);

        pPacker->FreeMem(pPacker->GetPackBuf());
        pPacker->Release();
        lpBizMessage->Release();
    }

    // 333017 证券委托撤单
    int ReqFunction333017(char* entrust_no)
    {
        cout<<"333017 证券委托撤单:"<<endl;
        int iRet = 0, hSend = 0;
        ///获取版本为2类型的pack打包器
        IF2Packer *pPacker = NewPacker(2);
        if(!pPacker)
        {
            printf("取打包器失败!\r\n");
            return -1;
        }
        pPacker->AddRef();
        ///定义解包器
        //IF2UnPacker *pUnPacker = NULL;

        IBizMessage* lpBizMessage = NewBizMessage();
        lpBizMessage->AddRef();

        ///应答业务消息
        IBizMessage* lpBizMessageRecv = NULL;
        //功能号
        lpBizMessage->SetFunction(333017);
        lpBizMessage->SetSubSystemNo(1000);
        lpBizMessage->SetCompanyID(91000);
        //请求类型
        lpBizMessage->SetPacketType(REQUEST_PACKET);
        lpBizMessage->SetSystemNo(iSystemNo);
        ///其他的应答信息
        LPRET_DATA pRetData = NULL;

        ///开始打包
        pPacker->BeginPack();
        ///加入字段名
        pPacker->AddField("op_branch_no", 'I', 5);//名字 类型 长度
        pPacker->AddField("op_entrust_way", 'C', 1);
        pPacker->AddField("op_station", 'S', 255);
        pPacker->AddField("branch_no", 'I', 5);
        pPacker->AddField("client_id", 'S', 18);//客户ID
        pPacker->AddField("fund_account", 'S', 18);//资金账号
        pPacker->AddField("password", 'S', 10);
        pPacker->AddField("password_type", 'C', 1);
        pPacker->AddField("user_token", 'S', 64);
        pPacker->AddField("batch_flag", 'S', 15);
        pPacker->AddField("exchange_type", 'S', 4);
        pPacker->AddField("entrust_no", 'S', 6);//委托编号
        ///加入对应的字段值
        pPacker->AddInt(m_op_branch_no);
        pPacker->AddChar(m_EntrustWay);
        pPacker->AddStr(m_opStation.c_str());
        pPacker->AddInt(m_BranchNo);
        pPacker->AddStr(m_client_id);
        pPacker->AddStr(m_AccountName);
        pPacker->AddStr(m_Password);
        pPacker->AddChar('2');
        pPacker->AddStr(m_opUserToken);
        pPacker->AddStr("");
        pPacker->AddStr("");
        pPacker->AddStr(entrust_no);
        ///结束打包
        pPacker->EndPack();

        lpBizMessage->SetContent(pPacker->GetPackBuf(),pPacker->GetPackLen());
        lpConnection->SendBizMsg(lpBizMessage, 1);

        pPacker->FreeMem(pPacker->GetPackBuf());
        pPacker->Release();
        lpBizMessage->Release();
        return 0;
    }

    //333101证券委托查询
    int ReqFunction333101()
    {
        cout<<"333101委托查询入参:"<<endl;
        int iRet = 0, hSend = 0;
        ///获取版本为2类型的pack打包器
        IF2Packer *pPacker = NewPacker(2);
        if(!pPacker)
        {
            printf("取打包器失败!\r\n");
            return -1;
        }
        pPacker->AddRef();

        ///定义解包器
        //IF2UnPacker *pUnPacker = NULL;

        ///创建业务消息接口
        IBizMessage* lpBizMessage = NewBizMessage();
        lpBizMessage->AddRef();
        ///应答业务消息
        IBizMessage* lpBizMessageRecv = NULL;
        //功能号
        lpBizMessage->SetFunction(333101);
        lpBizMessage->SetSubSystemNo(1000);
        lpBizMessage->SetCompanyID(91000);
        //请求类型
        lpBizMessage->SetPacketType(REQUEST_PACKET);
        lpBizMessage->SetSystemNo(iSystemNo);
        ///其他的应答信息
        LPRET_DATA pRetData = NULL;

        ///开始打包
        pPacker->BeginPack();
        ///加入字段名
        pPacker->AddField("op_branch_no", 'I', 5);//名字 类型 长度
        pPacker->AddField("op_entrust_way", 'C', 1);
        pPacker->AddField("op_station", 'S', 255);
        pPacker->AddField("branch_no", 'I', 5);
        pPacker->AddField("client_id", 'S', 18);//客户ID
        pPacker->AddField("fund_account", 'S', 18);//资金账号
        pPacker->AddField("password", 'S', 10);
        //pPacker->AddField("password_type", 'C', 1);
        pPacker->AddField("user_token", 'S', 64);
        //pPacker->AddField("exchange_type", 'S', 4);
        //pPacker->AddField("stcok_account",'S',11);
        //pPacker->AddField("stock_code",'S',16);
        //pPacker->AddField("sort_direction",'C',1);
        //pPacker->AddField("report_no",'I',8);
        //pPacker->AddField("action_in",'I',5);
        //pPacker->AddField("locate_entrust_no",'I',8);
        //pPacker->AddField("query_type",'C',1);
        //pPacker->AddField("query_mode",'C',1);
        //pPacker->AddField("position_str",'S',100);
        pPacker->AddField("request_num",'I',10);
        //pPacker->AddField("etf_flag",'C',1);
        ///加入对应的字段值
        pPacker->AddInt(m_op_branch_no);
        pPacker->AddChar(m_EntrustWay);
        pPacker->AddStr(m_opStation.c_str());
        pPacker->AddInt(m_BranchNo);
        pPacker->AddStr(m_client_id);
        pPacker->AddStr(m_AccountName);
        pPacker->AddStr(m_Password);
        //	pPacker->AddChar('2');
        pPacker->AddStr(m_opUserToken);
        //pPacker->AddStr("");
        //pPacker->AddStr("");
        //pPacker->AddStr("");
        //pPacker->AddChar(' ');
        //pPacker->AddInt( );
        //pPacker->AddInt( );
        //pPacker->AddInt( );
        //pPacker->AddChar(' ');
        //pPacker->AddChar(' ');
        //pPacker->AddStr("");
        pPacker->AddInt(100);
        //pPacker->AddChar(' ');
        ///结束打包
        pPacker->EndPack();

        ///设置业务内容
        lpBizMessage->SetContent(pPacker->GetPackBuf(),pPacker->GetPackLen());

        // 打印入参信息
        IF2UnPacker * lpUnPacker = NewUnPacker(pPacker->GetPackBuf(),pPacker->GetPackLen());
        lpUnPacker->AddRef();
        ShowPacket(lpUnPacker);
        lpUnPacker->Release();

        ///发送业务数据
        lpConnection->SendBizMsg(lpBizMessage, 1);
        pPacker->FreeMem(pPacker->GetPackBuf()); // 释放打包内存
        pPacker->Release();
        lpBizMessage->Release();
        return 0;
    }

    //333102证券成交查询
    int ReqFunction333102()
    {
        cout<<"333102证券成交查询入参"<<endl;
        int iRet = 0, hSend = 0;
        ///获取版本为2类型的pack打包器
        IF2Packer *pPacker = NewPacker(2);
        if(!pPacker)
        {
            printf("取打包器失败!\r\n");
            return -1;
        }
        pPacker->AddRef();
        ///定义解包器
        //IF2UnPacker *pUnPacker = NULL;

        IBizMessage* lpBizMessage = NewBizMessage();
        lpBizMessage->AddRef();
        ///应答业务消息
        IBizMessage* lpBizMessageRecv = NULL;
        //功能号
        lpBizMessage->SetFunction(333102);
        lpBizMessage->SetSubSystemNo(1000);
        lpBizMessage->SetCompanyID(91000);
        //请求类型
        lpBizMessage->SetPacketType(REQUEST_PACKET);
        lpBizMessage->SetSystemNo(iSystemNo);
        ///其他的应答信息
        LPRET_DATA pRetData = NULL;

        ///开始打包
        pPacker->BeginPack();
        ///加入字段名
        pPacker->AddField("op_branch_no", 'I', 5);//名字 类型 长度
        pPacker->AddField("op_entrust_way", 'C', 1);
        pPacker->AddField("op_station", 'S', 255);
        pPacker->AddField("branch_no", 'I', 5);
        pPacker->AddField("client_id", 'S', 18);//客户ID
        pPacker->AddField("fund_account", 'S', 18);//资金账号
        pPacker->AddField("password", 'S', 10);
        pPacker->AddField("password_type", 'C', 1);
        pPacker->AddField("user_token", 'S', 64);
        //pPacker->AddField("exchange_type", 'S', 4);
        //pPacker->AddField("stcok_account",'S',11);
        //pPacker->AddField("stock_code",'S',16);
        //pPacker->AddField("serial_no",'I',8);
        //pPacker->AddField("query_direction",'C',1);
        //pPacker->AddField("report_no",'I',8);
        //pPacker->AddField("query_type",'C',1);
        //pPacker->AddField("query_mode",'C',1);
        //pPacker->AddField("position_str",'S',100);
        //pPacker->AddField("request_num",'I',10);
        //pPacker->AddField("etf_flag",'C',1);
        ///加入对应的字段值
        pPacker->AddInt(m_op_branch_no);
        pPacker->AddChar(m_EntrustWay);
        pPacker->AddStr(m_opStation.c_str());
        pPacker->AddInt(m_BranchNo);
        pPacker->AddStr(m_client_id);
        pPacker->AddStr(m_AccountName);
        pPacker->AddStr(m_Password);
        pPacker->AddChar('2');
        pPacker->AddStr(m_opUserToken);
        //pPacker->AddStr("");
        //pPacker->AddStr("");
        //pPacker->AddStr("");
        //pPacker->AddInt();
        //pPacker->AddChar(' ');
        //pPacker->AddInt( );
        //pPacker->AddChar(' ');
        //pPacker->AddChar(' ');
        //pPacker->AddStr("");
        //pPacker->AddInt();
        //pPacker->AddChar(' ');
        pPacker->EndPack();
        lpBizMessage->SetContent(pPacker->GetPackBuf(),pPacker->GetPackLen());
        //打印入参信息
        IF2UnPacker * lpUnPacker = NewUnPacker(pPacker->GetPackBuf(),pPacker->GetPackLen());
        lpUnPacker->AddRef();
        ShowPacket(lpUnPacker);
        lpUnPacker->Release();

        lpConnection->SendBizMsg(lpBizMessage, 1);
        pPacker->FreeMem(pPacker->GetPackBuf());
        pPacker->Release();
        lpBizMessage->Release();
        return 0;
    }

    // 620001 订阅回报
    int SubFunction620001(int issue_type)
    {
        int iRet = 0, hSend = 0;
        IF2UnPacker *pMCUnPacker = NULL;
        ///获取版本为2类型的pack打包器
        IF2Packer *pPacker = NewPacker(2);
        if(!pPacker)
        {
            printf("取打包器失败!\r\n");
            return -1;
        }
        pPacker->AddRef();

        ///定义解包器
        //IF2UnPacker *pUnPacker = NULL;

        IBizMessage* lpBizMessage = NewBizMessage();
        lpBizMessage->AddRef();
        ///应答业务消息
        IBizMessage* lpBizMessageRecv = NULL;
        //功能号
        lpBizMessage->SetFunction(MSGCENTER_FUNC_REG);
        if (issue_type == 12) {
            lpBizMessage->SetSequeceNo(12);
        } else if (issue_type == 23) {
            lpBizMessage->SetSequeceNo(13);
        }
        //请求类型
        lpBizMessage->SetPacketType(REQUEST_PACKET);

        ///开始打包
        pPacker->BeginPack();
        ///加入字段名
        pPacker->AddField("branch_no", 'I', 5);
        pPacker->AddField("fund_account", 'S', 18);
        pPacker->AddField("op_branch_no", 'I', 5);
        pPacker->AddField("op_entrust_way",'C',1);
        pPacker->AddField("op_station", 'S', 255);
        pPacker->AddField("client_id",'S',18);
        pPacker->AddField("password",'S',10);
        pPacker->AddField("user_token", 'S', 64);
        pPacker->AddField("issue_type",'I',8);
        ///加入对应的字段值
        pPacker->AddInt(m_BranchNo);
        pPacker->AddStr(m_AccountName);
        pPacker->AddInt(m_op_branch_no);
        pPacker->AddChar(m_EntrustWay);
        pPacker->AddStr(m_opStation.c_str());	//op_station
        pPacker->AddStr(m_client_id);
        pPacker->AddStr(m_Password);
        pPacker->AddStr(m_opUserToken);
        pPacker->AddInt(issue_type);
        ///结束打包
        pPacker->EndPack();

        lpBizMessage->SetKeyInfo(pPacker->GetPackBuf(),pPacker->GetPackLen());
        lpConnection->SendBizMsg(lpBizMessage,1);

        pPacker->FreeMem(pPacker->GetPackBuf());
        pPacker->Release();
        lpBizMessage->Release();
    }

    // 620002 取消订阅回报
    int SubFunction620002(int issue_type)
    {
        int iRet = 0, hSend = 0;
        IF2UnPacker *pMCUnPacker = NULL;
        ///获取版本为2类型的pack打包器
        IF2Packer *pPacker = NewPacker(2);
        if (!pPacker)
        {
            printf("取打包器失败!\r\n");
            return -1;
        }
        pPacker->AddRef();

        IBizMessage* lpBizMessage = NewBizMessage();
        lpBizMessage->AddRef();
        ///应答业务消息
        IBizMessage* lpBizMessageRecv = NULL;
        //功能号
        lpBizMessage->SetFunction(MSGCENTER_FUNC_REG_CANCLE);
        if (issue_type == 12) {
            lpBizMessage->SetSequeceNo(14);
        } else if (issue_type == 23) {
            lpBizMessage->SetSequeceNo(15);
        }
        //请求类型
        lpBizMessage->SetPacketType(REQUEST_PACKET);

        ///开始打包
        pPacker->BeginPack();
        ///加入字段名
        pPacker->AddField("branch_no", 'I', 5);
        pPacker->AddField("fund_account", 'S', 18);
        pPacker->AddField("op_branch_no", 'I', 5);
        pPacker->AddField("op_entrust_way",'C',1);
        pPacker->AddField("op_station", 'S', 255);
        pPacker->AddField("client_id",'S',18);
        pPacker->AddField("password",'S',10);
        pPacker->AddField("user_token", 'S', 64);
        pPacker->AddField("issue_type",'I',8);
        ///加入对应的字段值
        pPacker->AddInt(m_BranchNo);
        pPacker->AddStr(m_AccountName);
        pPacker->AddInt(m_op_branch_no);
        pPacker->AddChar(m_EntrustWay);
        pPacker->AddStr(m_opStation.c_str());	//op_station
        pPacker->AddStr(m_client_id);
        pPacker->AddStr(m_Password);
        pPacker->AddStr(m_opUserToken);
        pPacker->AddInt(issue_type);
        ///结束打包
        pPacker->EndPack();

        lpBizMessage->SetKeyInfo(pPacker->GetPackBuf(), pPacker->GetPackLen());
        lpConnection->SendBizMsg(lpBizMessage, 1);

        pPacker->FreeMem(pPacker->GetPackBuf());
        pPacker->Release();
        lpBizMessage->Release();
    }

private:
    CConfigInterface* lpConfig;
    CConnectionInterface *lpConnection;
    char pout[255];
    char m_AccountName[12];
    char m_Password[8];
    char m_EntrustWay;
    string m_FuturesAccount;
    string m_opStation;
};

int main(int argc, char* argv[])
{

    CCallback* cCallback = new CCallback();

    if (cCallback->InitConn() < 0) return -1;

    /// 异步登录开放
//    _semaphore.wait();


//     400 证券行情查询
    cCallback->ReqFunction400("2", "000001");
    _semaphore.wait();

    // 333101证券委托查询
//    cout << "\r\n查询委托" << endl;
//    cCallback->ReqFunction333101();
//    _semaphore.wait();

    // 333102 证券成交查询
//    cout << "\r\n查询成交" << endl;
//    cCallback->ReqFunction333102();
//    _semaphore.wait();

    // 333104 证券持仓查询
    cout << "\r\n查询证券持仓" << endl;
    cCallback->ReqFunction333104("");
    _semaphore.wait();

    // 331300 证券股东信息查询
    cout << "\r\n查询证券股东信息" << endl;
    cCallback->ReqFunction331300();
    _semaphore.wait();

    // 如需订阅消息类型,放开下面的代码即可; 订阅成功后，由消息中心推送订阅给客户
    cout << "\r\n620001_12订阅证券成交回报" << endl;
    cCallback->SubFunction620001(ISSUE_TYPE_REALTIME_SECU);
    _semaphore.wait();
    cout << "\r\n620001_23订阅证券委托回报" << endl;
    cCallback->SubFunction620001(ISSUE_TYPE_ENTR_BACK);
    _semaphore.wait();

    // 如需订阅消息类型,放开下面的代码即可; 订阅成功后，由消息中心推送订阅给客户
    cout << "\r\n620002_12订阅证券成交回报" << endl;
    cCallback->SubFunction620002(ISSUE_TYPE_REALTIME_SECU);
    _semaphore.wait();
    cout << "\r\n620002_23订阅证券委托回报" << endl;
    cCallback->SubFunction620002(ISSUE_TYPE_ENTR_BACK);
    _semaphore.wait();

    // 如需下单、撤单，放开下面的代码即可
    // 333002 普通委托
//    cout << "\r\n按任意键下单 ...";
//    getchar(); cin.get();
//    // entrust_prop: U:最优五档即时成交剩余撤销
//    cCallback->ReqFunction333002("2", "000001", 100, NULL, '2', "U");
//    _semaphore.wait();
//
//    cout << "\r\n按任意键下单 ...";
//    getchar(); cin.get();
//    // entrust_prop: 0:买卖
//    cCallback->ReqFunction333002("2", "000001", 100, 14, '1', "0");
//    _semaphore.wait();

    // 33017 证券委托撤单
//    this_thread::sleep_for(chrono::milliseconds(1000));
//    cout << "\r\n按任意键撤单 ...";
//    getchar(); cin.get();
//    cCallback->ReqFunction333017("19");
//    _semaphore.wait();

    cout << "\r\n按任意键退出 ..." << endl;
    getchar(); cin.get();
    delete cCallback;
    return 0;
}
