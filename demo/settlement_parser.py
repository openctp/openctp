import re
import pandas as pd
from datetime import datetime

class SettlementParser:
    def __init__(self, file_path):
        """初始化结算单解析器"""
        self.file_path = file_path
        self.content = self._read_file()
        self.settlement_date = None
        self.client_info = {}
        self.account_summary = {}
        self.deposit_withdrawal = []
        self.transactions = []
        self.position_closed = []
        self.positions_detail = []
        self.positions_summary = []
        
    def _read_file(self):
        """读取结算单文件内容"""
        try:
            with open(self.file_path, 'r', encoding='utf-8') as file:
                return file.read()
        except UnicodeDecodeError:
            # 尝试其他编码
            with open(self.file_path, 'r', encoding='gbk') as file:
                return file.read()
    
    def parse(self):
        """解析结算单内容"""
        self._parse_header()
        self._parse_account_summary()
        self._parse_deposit_withdrawal()
        self._parse_transactions()
        self._parse_position_closed()
        self._parse_positions_detail()
        self._parse_positions_summary()
        
    def _parse_header(self):
        """解析结算单头部信息"""
        # 解析结算单日期
        date_match = re.search(r'日期\s+Date:(\d+)', self.content)
        if date_match:
            self.settlement_date = date_match.group(1)
            
        # 解析客户信息
        client_id_match = re.search(r'客户号\s+Client ID:\s*(\S+)', self.content)
        client_name_match = re.search(r'客户名称\s+Client Name:\s*(\S+)', self.content)
        
        if client_id_match:
            self.client_info['client_id'] = client_id_match.group(1)
        if client_name_match:
            self.client_info['client_name'] = client_name_match.group(1)
    
    def _parse_account_summary(self):
        """解析账户资金状况"""
        patterns = {
            'balance_bf': r'期初结存\s+Balance b/f:\s+([\d.-]+)',
            'deposit_withdrawal': r'出\s*入\s*金\s+Deposit/Withdrawal:\s+([\d.-]+)',
            'realized_pl': r'平仓盈亏\s+Realized P/L:\s+([\d.-]+)',
            'mtm_pl': r'持仓盯市盈亏\s+MTM P/L:\s+([\d.-]+)',
            'exercise_pl': r'期权执行盈亏\s+Exercise P/L:\s+([\d.-]+)',
            'commission': r'手\s*续\s*费\s+Commission:\s+([\d.-]+)',
            'exercise_fee': r'行权手续费\s+Exercise Fee:\s+([\d.-]+)',
            'delivery_fee': r'交割手续费\s+Delivery Fee:\s+([\d.-]+)',
            'fx_pledge': r'货币质入\s+New FX Pledge:\s+([\d.-]+)',
            'fx_redemption': r'货币质出\s+FX Redemption:\s+([\d.-]+)',
            'pledge_change': r'质押变化金额\s+Chg in Pledge Amt:\s+([\d.-]+)',
            'premium_received': r'权利金收入\s+premium received:\s+([\d.-]+)',
            'premium_paid': r'权利金支出\s+premium paid:\s+([\d.-]+)',
            'initial_margin': r'基础保证金\s+Initial Margin:\s+([\d.-]+)',
            'balance_cf': r'期末结存\s+Balance c/f:\s+([\d.-]+)',
            'pledge_amount': r'质\s*押\s*金\s+Pledge Amount:\s+([\d.-]+)',
            'client_equity': r'客户权益\s+Client Equity:\s+([\d.-]+)',
            'fx_pledge_occ': r'货币质押保证金占用\s+FX Pledge Occ.:\s+([\d.-]+)',
            'margin_occupied': r'保证金占用\s+Margin Occupied:\s+([\d.-]+)',
            'delivery_margin': r'交割保证金\s+Delivery Margin:\s+([\d.-]+)',
            'market_value_long': r'多头期权市值\s+market value\(long\):\s+([\d.-]+)',
            'market_value_short': r'空头期权市值\s+market value\(short\):\s+([\d.-]+)',
            'market_value_equity': r'市值权益\s+market value\(equity\):\s+([\d.-]+)',
            'fund_avail': r'可用资金\s+Fund Avail:\s+([\d.-]+)',
            'risk_degree': r'风\s*险\s*度\s+Risk Degree:\s+([\d.-]+%)',
            'margin_call': r'应追加资金\s+Margin Call:\s+([\d.-]+)',
        }
        
        for key, pattern in patterns.items():
            match = re.search(pattern, self.content)
            if match:
                value = match.group(1).replace(',', '')  # 移除逗号
                try:
                    if '%' in value:
                        self.account_summary[key] = value
                    else:
                        self.account_summary[key] = float(value)
                except ValueError:
                    self.account_summary[key] = value
    
    def _parse_deposit_withdrawal(self):
        """解析出入金明细"""
        # 定位出入金明细表格
        deposit_section_match = re.search(r'出入金明细\s+Deposit/Withdrawal([\s\S]*?)-{10,}.*?\n\|共\s+(\d+)条\|', self.content)
        if not deposit_section_match:
            return
        
        section_content = deposit_section_match.group(1)
        total_rows = int(deposit_section_match.group(2))
        
        # 找到表格内容行
        rows = re.findall(r'\|(.*?)\|(.*?)\|(.*?)\|(.*?)\|(.*?)\|', section_content)
        
        # 跳过表头
        if len(rows) >= 2:
            # 取得表头后的数据行
            data_rows = rows[2:]
            
            for row in data_rows:
                if '共' in row[0]:  # 跳过汇总行
                    continue
                    
                data = {
                    'date': row[0].strip(),
                    'type': row[1].strip(),
                    'deposit': float(row[2].strip().replace(',', '')) if row[2].strip() and row[2].strip() != '0.00' else 0,
                    'withdrawal': float(row[3].strip().replace(',', '')) if row[3].strip() and row[3].strip() != '0.00' else 0,
                    'note': row[4].strip()
                }
                self.deposit_withdrawal.append(data)
    
    def _parse_transactions(self):
        """解析成交记录"""
        # 定位成交记录表格
        transaction_section_match = re.search(r'成交记录\s+Transaction Record([\s\S]*?)(?=共\s+\d+条\|)', self.content)
        if not transaction_section_match:
            return
        
        section_content = transaction_section_match.group(1)
        
        # 找出表格总行数
        total_match = re.search(r'共\s+(\d+)条\|', self.content[transaction_section_match.end():transaction_section_match.end()+100])
        total_rows = int(total_match.group(1)) if total_match else 0
        
        # 找到表格内容行
        rows = re.findall(r'\|(.*?)\|(.*?)\|(.*?)\|(.*?)\|(.*?)\|(.*?)\|(.*?)\|(.*?)\|(.*?)\|(.*?)\|(.*?)\|(.*?)\|(.*?)\|(.*?)\|(.*?)\|', section_content)
        
        # 跳过表头
        if len(rows) >= 2:
            # 取得表头后的数据行
            data_rows = rows[2:]
            
            for row in data_rows:
                if '共' in row[0]:  # 跳过汇总行
                    continue
                    
                data = {
                    'date': row[0].strip(),
                    'exchange': row[1].strip(),
                    'product': row[2].strip(),
                    'instrument': row[3].strip(),
                    'buy_sell': row[4].strip(),
                    'hedge_spec': row[5].strip(),
                    'price': float(row[6].strip().replace(',', '')) if row[6].strip() else 0,
                    'lots': int(row[7].strip()) if row[7].strip() else 0,
                    'turnover': float(row[8].strip().replace(',', '')) if row[8].strip() else 0,
                    'open_close': row[9].strip(),
                    'fee': float(row[10].strip().replace(',', '')) if row[10].strip() else 0,
                    'realized_pl': float(row[11].strip().replace(',', '')) if row[11].strip() else 0,
                    'premium': float(row[12].strip().replace(',', '')) if row[12].strip() else 0,
                    'trans_no': row[13].strip(),
                    'trade_type': row[14].strip()
                }
                self.transactions.append(data)
            
            # 验证解析的数据条数是否与结算单中的总条数匹配
            if total_rows > 0 and len(self.transactions) != total_rows:
                print(f"警告: 成交记录解析不完整，总条数应为 {total_rows}，实际解析 {len(self.transactions)} 条")
    
    def _parse_position_closed(self):
        """解析平仓明细"""
        # 定位平仓明细表格
        closed_section_match = re.search(r'平仓明细\s+Position Closed([\s\S]*?)(?=共\s+\d+条\|)', self.content)
        if not closed_section_match:
            return
        
        section_content = closed_section_match.group(1)
        
        # 找出表格总行数
        total_match = re.search(r'共\s+(\d+)条\|', self.content[closed_section_match.end():closed_section_match.end()+100])
        total_rows = int(total_match.group(1)) if total_match else 0
        
        # 找到表格内容行
        rows = re.findall(r'\|(.*?)\|(.*?)\|(.*?)\|(.*?)\|(.*?)\|(.*?)\|(.*?)\|(.*?)\|(.*?)\|(.*?)\|(.*?)\|(.*?)\|', section_content)
        
        # 跳过表头
        if len(rows) >= 2:
            # 取得表头后的数据行
            data_rows = rows[2:]
            
            for row in data_rows:
                if '共' in row[0]:  # 跳过汇总行
                    continue
                    
                data = {
                    'close_date': row[0].strip(),
                    'exchange': row[1].strip(),
                    'product': row[2].strip(),
                    'instrument': row[3].strip(),
                    'open_date': row[4].strip(),
                    'buy_sell': row[5].strip(),
                    'lots': int(row[6].strip()) if row[6].strip() else 0,
                    'open_price': float(row[7].strip().replace(',', '')) if row[7].strip() else 0,
                    'prev_settlement': float(row[8].strip().replace(',', '')) if row[8].strip() else 0,
                    'trans_price': float(row[9].strip().replace(',', '')) if row[9].strip() else 0,
                    'realized_pl': float(row[10].strip().replace(',', '')) if row[10].strip() else 0,
                    'premium': float(row[11].strip().replace(',', '')) if row[11].strip() else 0
                }
                self.position_closed.append(data)
            
            # 验证解析的数据条数是否与结算单中的总条数匹配
            if total_rows > 0 and len(self.position_closed) != total_rows:
                print(f"警告: 平仓明细解析不完整，总条数应为 {total_rows}，实际解析 {len(self.position_closed)} 条")
    
    def _parse_positions_detail(self):
        """解析持仓明细"""
        # 定位持仓明细表格
        positions_section_match = re.search(r'持仓明细\s+Positions Detail([\s\S]*?)(?=共\s+\d+条\|)', self.content)
        if not positions_section_match:
            return
        
        section_content = positions_section_match.group(1)
        
        # 找出表格总行数
        total_match = re.search(r'共\s+(\d+)条\|', self.content[positions_section_match.end():positions_section_match.end()+100])
        total_rows = int(total_match.group(1)) if total_match else 0
        
        # 找到表格内容行
        rows = re.findall(r'\|(.*?)\|(.*?)\|(.*?)\|(.*?)\|(.*?)\|(.*?)\|(.*?)\|(.*?)\|(.*?)\|(.*?)\|(.*?)\|(.*?)\|(.*?)\|(.*?)\|', section_content)
        
        # 跳过表头
        if len(rows) >= 2:
            # 取得表头后的数据行
            data_rows = rows[2:]
            
            for row in data_rows:
                if '共' in row[0]:  # 跳过汇总行
                    continue
                    
                data = {
                    'exchange': row[0].strip(),
                    'product': row[1].strip(),
                    'instrument': row[2].strip(),
                    'open_date': row[3].strip(),
                    'hedge_spec': row[4].strip(),
                    'buy_sell': row[5].strip(),
                    'position': int(row[6].strip()) if row[6].strip() else 0,
                    'open_price': float(row[7].strip().replace(',', '')) if row[7].strip() else 0,
                    'prev_settlement': float(row[8].strip().replace(',', '')) if row[8].strip() else 0,
                    'settlement_price': float(row[9].strip().replace(',', '')) if row[9].strip() else 0,
                    'accum_pl': float(row[10].strip().replace(',', '')) if row[10].strip() else 0,
                    'mtm_pl': float(row[11].strip().replace(',', '')) if row[11].strip() else 0,
                    'margin': float(row[12].strip().replace(',', '')) if row[12].strip() else 0,
                    'option_value': float(row[13].strip().replace(',', '')) if row[13].strip() else 0
                }
                self.positions_detail.append(data)
            
            # 验证解析的数据条数是否与结算单中的总条数匹配
            if total_rows > 0 and len(self.positions_detail) != total_rows:
                print(f"警告: 持仓明细解析不完整，总条数应为 {total_rows}，实际解析 {len(self.positions_detail)} 条")
    
    def _parse_positions_summary(self):
        """解析持仓汇总"""
        # 定位持仓汇总表格
        summary_section_match = re.search(r'持仓汇总\s+Positions([\s\S]*?)(?=共\s+\d+条\|)', self.content)
        if not summary_section_match:
            return
        
        section_content = summary_section_match.group(1)
        
        # 找出表格总行数
        total_match = re.search(r'共\s+(\d+)条\|', self.content[summary_section_match.end():summary_section_match.end()+100])
        total_rows = int(total_match.group(1)) if total_match else 0
        
        # 找到表格内容行
        rows = re.findall(r'\|(.*?)\|(.*?)\|(.*?)\|(.*?)\|(.*?)\|(.*?)\|(.*?)\|(.*?)\|(.*?)\|(.*?)\|(.*?)\|(.*?)\|(.*?)\|', section_content)
        
        # 跳过表头
        if len(rows) >= 2:
            # 取得表头后的数据行
            data_rows = rows[2:]
            
            for row in data_rows:
                if '共' in row[0]:  # 跳过汇总行
                    continue
                    
                data = {
                    'product': row[0].strip(),
                    'instrument': row[1].strip(),
                    'long_pos': int(row[2].strip()) if row[2].strip() else 0,
                    'avg_buy_price': float(row[3].strip().replace(',', '')) if row[3].strip() else 0,
                    'short_pos': int(row[4].strip()) if row[4].strip() else 0,
                    'avg_sell_price': float(row[5].strip().replace(',', '')) if row[5].strip() else 0,
                    'prev_settlement': float(row[6].strip().replace(',', '')) if row[6].strip() else 0,
                    'settlement': float(row[7].strip().replace(',', '')) if row[7].strip() else 0,
                    'mtm_pl': float(row[8].strip().replace(',', '')) if row[8].strip() else 0,
                    'margin': float(row[9].strip().replace(',', '')) if row[9].strip() else 0,
                    'hedge_spec': row[10].strip(),
                    'option_value_long': float(row[11].strip().replace(',', '')) if row[11].strip() else 0,
                    'option_value_short': float(row[12].strip().replace(',', '')) if row[12].strip() else 0
                }
                self.positions_summary.append(data)
            
            # 验证解析的数据条数是否与结算单中的总条数匹配
            if total_rows > 0 and len(self.positions_summary) != total_rows:
                print(f"警告: 持仓汇总解析不完整，总条数应为 {total_rows}，实际解析 {len(self.positions_summary)} 条")
    
    def get_dataframes(self):
        """将所有解析的数据转换为DataFrame"""
        dfs = {
            'client_info': pd.DataFrame([self.client_info]),
            'account_summary': pd.DataFrame([self.account_summary]),
            'deposit_withdrawal': pd.DataFrame(self.deposit_withdrawal) if self.deposit_withdrawal else pd.DataFrame(),
            'transactions': pd.DataFrame(self.transactions) if self.transactions else pd.DataFrame(),
            'position_closed': pd.DataFrame(self.position_closed) if self.position_closed else pd.DataFrame(),
            'positions_detail': pd.DataFrame(self.positions_detail) if self.positions_detail else pd.DataFrame(),
            'positions_summary': pd.DataFrame(self.positions_summary) if self.positions_summary else pd.DataFrame()
        }
        return dfs
    
    def save_to_excel(self, output_path):
        """将所有数据保存到Excel文件"""
        dfs = self.get_dataframes()
        
        with pd.ExcelWriter(output_path) as writer:
            dfs['client_info'].to_excel(writer, sheet_name='客户信息', index=False)
            dfs['account_summary'].to_excel(writer, sheet_name='资金状况', index=False)
            
            if not dfs['deposit_withdrawal'].empty:
                dfs['deposit_withdrawal'].to_excel(writer, sheet_name='出入金明细', index=False)
            
            if not dfs['transactions'].empty:
                dfs['transactions'].to_excel(writer, sheet_name='成交记录', index=False)
            
            if not dfs['position_closed'].empty:
                dfs['position_closed'].to_excel(writer, sheet_name='平仓明细', index=False)
            
            if not dfs['positions_detail'].empty:
                dfs['positions_detail'].to_excel(writer, sheet_name='持仓明细', index=False)
            
            if not dfs['positions_summary'].empty:
                dfs['positions_summary'].to_excel(writer, sheet_name='持仓汇总', index=False)
                
        print(f"结算单数据已保存到: {output_path}")
        
    def validate_parsing(self):
        """验证解析的完整性"""
        result = {
            'complete': True,
            'summary': {}
        }
        
        # 验证客户信息
        if not self.client_info:
            result['complete'] = False
            result['summary']['client_info'] = '未解析到客户信息'
        
        # 验证资金状况
        expected_keys = ['balance_bf', 'realized_pl', 'mtm_pl', 'commission', 'balance_cf', 'client_equity']
        missing_keys = [key for key in expected_keys if key not in self.account_summary]
        if missing_keys:
            result['complete'] = False
            result['summary']['account_summary'] = f'资金状况缺少字段: {", ".join(missing_keys)}'
        
        # 输出验证结果
        return result

def main():
    """主函数"""
    settlement_file = "settlement.txt"
    parser = SettlementParser(settlement_file)
    parser.parse()
    
    # 验证解析的完整性
    validation = parser.validate_parsing()
    if not validation['complete']:
        print("\n警告: 解析不完整!")
        for section, msg in validation['summary'].items():
            print(f"- {section}: {msg}")
    
    # 获取结算单日期作为文件名的一部分
    date_str = parser.settlement_date or datetime.now().strftime('%Y%m%d')
    output_file = f"settlement_parsed_{date_str}.xlsx"
    
    parser.save_to_excel(output_file)
    
    # 打印账户资金摘要
    print("\n==== 账户资金概况 ====")
    print(f"客户ID: {parser.client_info.get('client_id', 'N/A')}")
    print(f"客户名称: {parser.client_info.get('client_name', 'N/A')}")
    print(f"结算日期: {parser.settlement_date or 'N/A'}")
    print(f"期初结存: {parser.account_summary.get('balance_bf', 'N/A')}")
    print(f"平仓盈亏: {parser.account_summary.get('realized_pl', 'N/A')}")
    print(f"持仓盯市盈亏: {parser.account_summary.get('mtm_pl', 'N/A')}")
    print(f"手续费: {parser.account_summary.get('commission', 'N/A')}")
    print(f"期末结存: {parser.account_summary.get('balance_cf', 'N/A')}")
    print(f"客户权益: {parser.account_summary.get('client_equity', 'N/A')}")
    print(f"可用资金: {parser.account_summary.get('fund_avail', 'N/A')}")
    print(f"风险度: {parser.account_summary.get('risk_degree', 'N/A')}")
    
    # 打印交易统计
    print("\n==== 交易统计 ====")
    if parser.transactions:
        tx_df = pd.DataFrame(parser.transactions)
        print(f"总成交笔数: {len(tx_df)}")
        print(f"总成交手数: {tx_df['lots'].sum()}")
        print(f"总成交金额: {tx_df['turnover'].sum():.2f}")
        print(f"总手续费: {tx_df['fee'].sum():.2f}")
        print(f"总平仓盈亏: {tx_df['realized_pl'].sum():.2f}")
    else:
        print("无成交记录")
    
    # 打印持仓汇总
    print("\n==== 持仓汇总 ====")
    if parser.positions_summary:
        pos_df = pd.DataFrame(parser.positions_summary)
        print(f"合约品种数: {len(pos_df)}")
        print(f"买持仓总量: {pos_df['long_pos'].sum()}")
        print(f"卖持仓总量: {pos_df['short_pos'].sum()}")
        print(f"持仓盯市盈亏: {pos_df['mtm_pl'].sum():.2f}")
        print(f"保证金占用: {pos_df['margin'].sum():.2f}")
    else:
        print("无持仓记录")

if __name__ == "__main__":
    main() 