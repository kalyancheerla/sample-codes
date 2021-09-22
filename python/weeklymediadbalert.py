#!/usr/bin/env python3

import datetime, sqlite3

MEDIA_DB = "media.db"

def main():
    db_conn = sqlite3.connect(MEDIA_DB)
    sql_query = "SELECT id,title,category FROM telugu WHERE " \
                "pubDate > ?;"
    week_ago = (datetime.date.today() - datetime.timedelta(days=7)).strftime('%Y-%m-%d')
    records = db_conn.execute(sql_query, (week_ago,))
    for record in records:
        print(record)

if __name__ == "__main__":
    main()
