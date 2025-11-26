#include "generator.hh"

/////////////////////////////////////////////////////////////////////////////////////////////////////
// html response generator
/////////////////////////////////////////////////////////////////////////////////////////////////////

std::string html_generator::generate_dashboard(finmart_db& db)
{
  std::stringstream html;

  html << R"(<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>FinLite - Financial Reporting Platform</title>
    <style>
        * {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
        }
        
        body {
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
            background: #f5f7fa;
            color: #333;
        }
        
        .platform-badge {
            position: fixed;
            top: 10px;
            right: 10px;
            background: #667eea;
            color: white;
            padding: 8px 15px;
            border-radius: 20px;
            font-size: 0.85em;
            font-weight: bold;
            z-index: 1000;
        }
        
        .header {
            background: linear-gradient(135deg, #1e3c72 0%, #2a5298 100%);
            color: white;
            padding: 20px 40px;
            box-shadow: 0 2px 10px rgba(0,0,0,0.1);
        }
        
        .header h1 {
            font-size: 2em;
            margin-bottom: 5px;
        }
        
        .header p {
            opacity: 0.9;
            font-size: 0.95em;
        }
        
        .container {
            max-width: 1400px;
            margin: 0 auto;
            padding: 30px;
        }
        
        .stats-grid {
            display: grid;
            grid-template-columns: repeat(auto-fit, minmax(250px, 1fr));
            gap: 20px;
            margin-bottom: 30px;
        }
        
        .stat-card {
            background: white;
            padding: 25px;
            border-radius: 10px;
            box-shadow: 0 2px 8px rgba(0,0,0,0.1);
            border-left: 4px solid #667eea;
        }
        
        .stat-card h3 {
            color: #666;
            font-size: 0.9em;
            text-transform: uppercase;
            margin-bottom: 10px;
        }
        
        .stat-card .value {
            font-size: 2em;
            font-weight: bold;
            color: #1e3c72;
        }
        
        .chart-container {
            background: white;
            padding: 30px;
            border-radius: 10px;
            box-shadow: 0 2px 8px rgba(0,0,0,0.1);
            margin-bottom: 30px;
        }
        
        .chart-container h2 {
            margin-bottom: 20px;
            color: #1e3c72;
            border-bottom: 2px solid #667eea;
            padding-bottom: 10px;
        }
        
        .bar-chart {
            display: flex;
            flex-direction: column;
            gap: 15px;
        }
        
        .bar-item {
            display: flex;
            align-items: center;
            gap: 15px;
        }
        
        .bar-label {
            min-width: 120px;
            font-weight: 500;
        }
        
        .bar-visual {
            flex: 1;
            height: 30px;
            background: linear-gradient(90deg, #667eea 0%, #764ba2 100%);
            border-radius: 5px;
            position: relative;
            transition: all 0.3s;
        }
        
        .bar-visual:hover {
            transform: scaleX(1.02);
            box-shadow: 0 2px 8px rgba(102, 126, 234, 0.4);
        }
        
        .bar-value {
            min-width: 100px;
            text-align: right;
            font-weight: bold;
            color: #1e3c72;
        }
        
        .table-container {
            background: white;
            padding: 30px;
            border-radius: 10px;
            box-shadow: 0 2px 8px rgba(0,0,0,0.1);
            overflow-x: auto;
        }
        
        table {
            width: 100%;
            border-collapse: collapse;
        }
        
        th {
            background: #1e3c72;
            color: white;
            padding: 12px;
            text-align: left;
            font-weight: 600;
        }
        
        td {
            padding: 12px;
            border-bottom: 1px solid #eee;
        }
        
        tr:hover {
            background: #f8f9fa;
        }
        
        .status-approved {
            color: #28a745;
            font-weight: bold;
        }
        
        .status-pending {
            color: #ffc107;
            font-weight: bold;
        }
        
        .nav {
            background: white;
            padding: 15px 40px;
            box-shadow: 0 2px 5px rgba(0,0,0,0.1);
            margin-bottom: 0;
        }
        
        .nav a {
            color: #1e3c72;
            text-decoration: none;
            margin-right: 25px;
            font-weight: 500;
            transition: color 0.3s;
        }
        
        .nav a:hover {
            color: #667eea;
        }
        
        .nav a.active {
            color: #667eea;
            border-bottom: 2px solid #667eea;
            padding-bottom: 3px;
        }
        
        .badge {
            display: inline-block;
            padding: 4px 10px;
            border-radius: 12px;
            font-size: 0.85em;
            font-weight: 600;
        }
        
        .badge-peoplesoft { background: #e3f2fd; color: #1976d2; }
        .badge-coupa { background: #f3e5f5; color: #7b1fa2; }
        .badge-sap { background: #e8f5e9; color: #388e3c; }
        .badge-legacy { background: #fff3e0; color: #f57c00; }
    </style>
</head>
<body>
)";

  html << R"(    <div class="header">
        <h1>FinLite</h1>
        <p>Financial Reporting & Business Intelligence Platform</p>
    </div>
    <div class="container">
)";

  /////////////////////////////////////////////////////////////////////////////////////////////////////
  // statistics cards
  /////////////////////////////////////////////////////////////////////////////////////////////////////

  double total_spending = db.get_total_spending();
  std::vector<transaction> transactions = db.get_all_transactions();
  int approved_count = 0;
  int pending_count = 0;
  for (size_t idx = 0; idx < transactions.size(); ++idx)
  {
    if (transactions[idx].status == "Approved") approved_count++;
    else pending_count++;
  }

  html << R"(
        <div class="stats-grid">
            <div class="stat-card">
                <h3>Total Spending</h3>
                <div class="value">$)" << std::fixed << std::setprecision(2) << total_spending << R"(</div>
            </div>
            <div class="stat-card">
                <h3>Total Transactions</h3>
                <div class="value">)" << transactions.size() << R"(</div>
            </div>
            <div class="stat-card">
                <h3>Approved</h3>
                <div class="value">)" << approved_count << R"(</div>
            </div>
            <div class="stat-card">
                <h3>Pending Review</h3>
                <div class="value">)" << pending_count << R"(</div>
            </div>
        </div>
)";

  /////////////////////////////////////////////////////////////////////////////////////////////////////
  // department spending chart
  /////////////////////////////////////////////////////////////////////////////////////////////////////

  std::map<std::string, double> spending = db.get_department_spending();
  double max_spending = 0;
  for (std::map<std::string, double>::iterator it = spending.begin(); it != spending.end(); ++it)
  {
    if (it->second > max_spending)
    {
      max_spending = it->second;
    }
  }

  html << R"(
        <div class="chart-container">
            <h2>Spending by Department</h2>
            <div class="bar-chart">
)";

  for (std::map<std::string, double>::const_iterator pair = spending.begin(); pair != spending.end(); ++pair)
  {
    double percentage = (pair->second / max_spending) * 100;
    html << "                <div class=\"bar-item\">\n";
    html << "                    <div class=\"bar-label\">" << pair->first << "</div>\n";
    html << "                    <div class=\"bar-visual\" style=\"width: " << percentage << "%\"></div>\n";
    html << "                    <div class=\"bar-value\">$" << std::fixed << std::setprecision(2) << pair->second << "</div>\n";
    html << "                </div>\n";
  }

  html << R"(
            </div>
        </div>
)";

  /////////////////////////////////////////////////////////////////////////////////////////////////////
  // Source Systems Chart
  /////////////////////////////////////////////////////////////////////////////////////////////////////

  std::map<std::string, int> source_counts = db.get_source_system_counts();
  int max_count = 0;
  for (std::map<std::string, int>::const_iterator pair = source_counts.begin(); pair != source_counts.end(); ++pair)
  {
    if (pair->second > max_count) max_count = pair->second;
  }

  html << R"(
        <div class="chart-container">
            <h2>Transactions by Source System</h2>
            <div class="bar-chart">
)";

  for (std::map<std::string, int>::const_iterator pair = source_counts.begin(); pair != source_counts.end(); ++pair)
  {
    double percentage = ((double)pair->second / max_count) * 100;
    html << "                <div class=\"bar-item\">\n";
    html << "                    <div class=\"bar-label\">" << pair->first << "</div>\n";
    html << "                    <div class=\"bar-visual\" style=\"width: " << percentage << "%; background: linear-gradient(90deg, #2a5298 0%, #1e3c72 100%)\"></div>\n";
    html << "                    <div class=\"bar-value\">" << pair->second << " transactions</div>\n";
    html << "                </div>\n";
  }

  html << R"(
            </div>
        </div>
)";

  /////////////////////////////////////////////////////////////////////////////////////////////////////
  // recent transactions table
  /////////////////////////////////////////////////////////////////////////////////////////////////////

  html << R"(
        <div class="table-container">
            <h2>Recent Transactions</h2>
            <table>
                <thead>
                    <tr>
                        <th>ID</th>
                        <th>Date</th>
                        <th>Department</th>
                        <th>Category</th>
                        <th>Vendor</th>
                        <th>Amount</th>
                        <th>Status</th>
                        <th>Source</th>
                    </tr>
                </thead>
                <tbody>
)";

  int display_count = 0;
  for (std::vector<transaction>::const_iterator t = transactions.begin(); t != transactions.end(); ++t)
  {
    if (display_count++ >= 20) break;

    std::string status_class = (t->status == "Approved") ? "status-approved" : "status-pending";
    std::string badge_class = "badge-" + t->source_system;
    std::transform(badge_class.begin(), badge_class.end(), badge_class.begin(), ::tolower);

    html << "                    <tr>\n";
    html << "                        <td>" << t->id << "</td>\n";
    html << "                        <td>" << t->date << "</td>\n";
    html << "                        <td>" << t->department << "</td>\n";
    html << "                        <td>" << t->category << "</td>\n";
    html << "                        <td>" << t->vendor << "</td>\n";
    html << "                        <td>$" << std::fixed << std::setprecision(2) << t->amount << "</td>\n";
    html << "                        <td class=\"" << status_class << "\">" << t->status << "</td>\n";
    html << "                        <td><span class=\"badge " << badge_class << "\">" << t->source_system << "</span></td>\n";
    html << "                    </tr>\n";
  }

  html << R"(
                </tbody>
            </table>
        </div>
    </div>
</body>
</html>
)";

  return html.str();
}
