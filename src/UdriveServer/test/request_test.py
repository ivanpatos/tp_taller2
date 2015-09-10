#Ejecutar con pyhton request_test.py
#Importante: la base de datos debe estar vacia

import requests
import unittest

class TestRequests(unittest.TestCase):

	#login fallido
	def test_login(self):
		headersLogin = {'username': 'juan123', 'password': 'passjuan'}
		r = requests.post('http://localhost:8080/login', headers=headersLogin)
		jsonResponse = r.json()
		self.assertEqual("ERROR", jsonResponse["result"])
		self.assertEqual(2, jsonResponse["errorCode"])

	#creacion usuario, login y logout
	def test_create_user_and_login_and_logout(self):
		jsonCreateUser = {'username': 'juanperez', 'password': 'juanperez', 'name': 'Juan Perez', 'mail': 'juan_perez@gmail.com', 'profilePicture': 'qwdsad123123avvdsfdfd'}
		r = requests.post('http://localhost:8080/user', json=jsonCreateUser)
		jsonResponse = r.json()
		self.assertEqual("OK", jsonResponse["result"])
		self.assertEqual("juanperez", jsonResponse["data"]["username"])
		
		headersLogin = {'username': 'juanperez', 'password': 'juanperez'}
		r = requests.post('http://localhost:8080/login', headers=headersLogin)
		jsonResponse = r.json()
		self.assertEqual("OK", jsonResponse["result"])
		self.assertEqual("juanperez", jsonResponse["data"]["username"])

		headersLogout = {'username': jsonResponse["data"]["username"], 'token': jsonResponse["data"]["token"]}
		r = requests.post('http://localhost:8080/logout', headers=headersLogout)
		jsonResponse = r.json()
		self.assertEqual("OK", jsonResponse["result"])

	#get user
	def test_get_user(self):
		headersLogin = {'username': 'juanperez', 'password': 'juanperez'}
		r = requests.post('http://localhost:8080/login', headers=headersLogin)
		jsonResponse = r.json()
		self.assertEqual("OK", jsonResponse["result"])
		self.assertEqual("juanperez", jsonResponse["data"]["username"])

		headersGetUser={'username': jsonResponse["data"]["username"], 'token': jsonResponse["data"]["token"]}
		r = requests.get('http://localhost:8080/user?username=juanperez', headers=headersGetUser)
		jsonResponse = r.json()
		self.assertEqual("OK", jsonResponse["result"])
		self.assertEqual("juanperez", jsonResponse["data"]["username"])

	#update user
	def test_update_user(self):
		headersLogin={'username': 'juanperez', 'password': 'juanperez'}
		r = requests.post('http://localhost:8080/login', headers=headersLogin)
		jsonResponse = r.json()
		self.assertEqual("OK", jsonResponse["result"])
		self.assertEqual("juanperez", jsonResponse["data"]["username"])

		headersUpdateUser = {'username': jsonResponse["data"]["username"], 'token': jsonResponse["data"]["token"]}
		jsonUpdateUser = {'password': 'juanperez', 'name': 'Juan Perez Garcia', 'mail': 'juan_perez@gmail.com', 'profilePicture': 'qwdsad123123avvdsfdfd', 'lastLocation': 'asdsdasds'}
		r = requests.put('http://localhost:8080/user', headers=headersUpdateUser, json=jsonUpdateUser)
		jsonResponse = r.json()
		self.assertEqual("OK", jsonResponse["result"])
		self.assertEqual("Juan Perez Garcia", jsonResponse["data"]["name"])

	#get all users
	def test_get_all_users(self):
		jsonCreateUser = {'username': 'laura123', 'password': 'laurapass', 'name': 'Laura Rodriguez', 'mail': 'lau@gmail.com', 'profilePicture': 'pppppppp'}
		r = requests.post('http://localhost:8080/user', json=jsonCreateUser)
		jsonResponse = r.json()
		self.assertEqual("OK", jsonResponse["result"])
		self.assertEqual("laura123", jsonResponse["data"]["username"])

		headersLogin = {'username': 'juanperez', 'password': 'juanperez'}
		r = requests.post('http://localhost:8080/login', headers=headersLogin)
		jsonResponse = r.json()
		self.assertEqual("OK", jsonResponse["result"])
		self.assertEqual("juanperez", jsonResponse["data"]["username"])

		headersGetAllUsers = {'username': jsonResponse["data"]["username"], 'token': jsonResponse["data"]["token"]}
		r = requests.get('http://localhost:8080/user', headers=headersGetAllUsers)
		jsonResponse = r.json()
		self.assertEqual("OK", jsonResponse["result"])
		self.assertEqual("juanperez", jsonResponse["data"][0]["username"])
		self.assertEqual("laura123", jsonResponse["data"][1]["username"])

if __name__ == '__main__':
	suite = unittest.TestLoader().loadTestsFromTestCase(TestRequests)
	unittest.TextTestRunner(verbosity=2).run(suite)
