from flask import Flask, render_template, request
import sqlite3

app = Flask(__name__)

def getdata(query):
	#Connecting to sqlite
	conn = sqlite3.connect('data.db')
	#Creating a cursor object using the cursor() method
	cursor = conn.cursor()
	sql = query
	cursor.execute(sql)
	rows = cursor.fetchall()
	if rows != None:
		label = rows[0][0]
	else:
		label = 'nodata'
	# Commit your changes in the database
	conn.commit()
	#Closing the connection
	conn.close()
	return label

@app.route('/')
def index():
	return render_template("http.html")

@app.route('/insert',methods=['POST'])
def insert():
	if request.method == 'POST':
		temp = request.form['temperature']  
		hum = request.form['humidity']
		pps = request.form['pressure']
		rain = request.form['rain']
		data = (hum,temp,pps,rain)
		conn = sqlite3.connect('data.db')
		#Creating a cursor object using the cursor() method
		cursor = conn.cursor()
		sql ='''INSERT INTO data (humidity,temperature,pressure,result) VALUES (?,?,?,?)'''
		cursor.execute(sql,data) 
		# Commit your changes in the database
		conn.commit()
		#Closing the connection
		conn.close()
		return 'success'
		
	

@app.route('/reqlabel', methods=["GET","POST"])
def reqlabel():
	if request.method == 'POST' and request.form['key'] == 'getdataLabel':
		query = '''SELECT result FROM data ORDER BY ID DESC LIMIT 1'''
		label = getdata(query)
		return label

@app.route('/reqt', methods=["GET","POST"])
def reqt():
	if request.method == 'POST' and request.form['key'] == 'getdataTt':
		query='''SELECT temperature FROM data ORDER BY ID DESC LIMIT 1'''
		label = getdata(query)
		return str(label)

@app.route('/reqp', methods=["GET","POST"])
def reqp():
	if request.method == 'POST' and request.form['key'] == 'getdataPp':
		query='''SELECT pressure FROM data ORDER BY ID DESC LIMIT 1'''
		label = getdata(query)
		return str(label)

@app.route('/reqh', methods=["GET","POST"])
def reqh():
	if request.method == 'POST' and request.form['key'] == 'getdataHh':
		query='''SELECT humidity FROM data ORDER BY ID DESC LIMIT 1'''
		label = getdata(query)
		return str(label)

if __name__ == "__main__":
    app.run(debug=True)
    app.run(host='127.0.0.1', port=5000)