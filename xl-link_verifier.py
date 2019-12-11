#!/usr/bin/python3

# Title: xl-link_verifier
# Author: Kalyan Cheerla
# 12th June 2018 00:37:00
# Version: 0.1v
# Description:
# Solving a small problem of surya!
# Taking links data from a excel sheet & verifying that links are working or not!

import xlrd
import requests

wb = xlrd.open_workbook("sample.xlsx")
sh = wb.sheet_by_index(0)
for row in range(sh.nrows):
    try:
        data=requests.get(sh.cell_value(row,0))
        print("%d OK!" % data.status_code)
    except:
        print('Server is not responding')
