#Ejecutar con pyhton request_test.py
#Importante: la base de datos debe estar vacia

import requests
import unittest

class TestRequests(unittest.TestCase):

	#creacion usuario
	def test_create_user(self):
		jsonCreateUser = {'username': 'juanperez', 'password': 'juanperez', 'name': 'Juan Perez', 'mail': 'juan_perez@gmail.com', 'profilePicture': 'qwdsad123123avvdsfdfd'}
		r = requests.post('http://localhost:8080/user', json=jsonCreateUser)
		jsonResponse = r.json()
		self.assertEqual("OK", jsonResponse["result"])
		self.assertEqual("juanperez", jsonResponse["data"]["username"])
	
	#login y logout
	def test_login_and_logout(self):
		jsonLogin = {'username': 'juanperez', 'password': 'juanperez'}
		r = requests.post('http://localhost:8080/login', json=jsonLogin)
		jsonResponse = r.json()
		self.assertEqual("OK", jsonResponse["result"])
		self.assertEqual("juanperez", jsonResponse["data"]["username"])

		headersLogout = {'username': jsonResponse["data"]["username"], 'token': jsonResponse["data"]["token"]}
		r = requests.post('http://localhost:8080/logout', headers=headersLogout)
		jsonResponse = r.json()
		self.assertEqual("OK", jsonResponse["result"])

	#obtencion de metadatos del usuario
	def test_get_user(self):
		jsonLogin = {'username': 'juanperez', 'password': 'juanperez'}
		r = requests.post('http://localhost:8080/login', json=jsonLogin)
		jsonResponse = r.json()

		headersGetUser={'username': jsonResponse["data"]["username"], 'token': jsonResponse["data"]["token"]}
		r = requests.get('http://localhost:8080/user?username=juanperez', headers=headersGetUser)
		jsonResponse = r.json()
		self.assertEqual("OK", jsonResponse["result"])
		self.assertEqual("juanperez", jsonResponse["data"]["username"])

	#actualizacion de metadatos del usuario
	def test_update_user(self):
		jsonLogin={'username': 'juanperez', 'password': 'juanperez'}
		r = requests.post('http://localhost:8080/login', json=jsonLogin)
		jsonResponse = r.json()

		headersUpdateUser = {'username': jsonResponse["data"]["username"], 'token': jsonResponse["data"]["token"]}
		jsonUpdateUser = {'password': 'juanperez', 'name': 'Juan Perez Garcia', 'mail': 'juan_perez@gmail.com', 'profilePicture': 'qwdsad123123avvdsfdfd', 'lastLocation': 'asdsdasds'}
		r = requests.put('http://localhost:8080/user', headers=headersUpdateUser, json=jsonUpdateUser)
		jsonResponse = r.json()
		self.assertEqual("OK", jsonResponse["result"])
		self.assertEqual("Juan Perez Garcia", jsonResponse["data"]["name"])

	#obtencion de metadatos de todos los usuarios
	def test_get_all_users(self):
		jsonCreateUser = {'username': 'laura123', 'password': 'laurapass', 'name': 'Laura Rodriguez', 'mail': 'lau@gmail.com', 'profilePicture': 'pppppppp'}
		requests.post('http://localhost:8080/user', json=jsonCreateUser)

		jsonLogin = {'username': 'juanperez', 'password': 'juanperez'}
		r = requests.post('http://localhost:8080/login', json=jsonLogin)
		jsonResponse = r.json()

		headersGetAllUsers = {'username': jsonResponse["data"]["username"], 'token': jsonResponse["data"]["token"]}
		r = requests.get('http://localhost:8080/user', headers=headersGetAllUsers)
		jsonResponse = r.json()
		self.assertEqual("OK", jsonResponse["result"])
		self.assertEqual("juanperez", jsonResponse["data"][0]["username"])
		self.assertEqual("laura123", jsonResponse["data"][1]["username"])

	#creacion de archivo en carpeta root del usuario
	def test_create_file(self):
		jsonCreateUser = {'username': 'tptaller2', 'password': 'pass', 'name': 'tp taller2', 'mail': 'tptaller2@gmail.com', 'profilePicture': 'qwerty'}
		requests.post('http://localhost:8080/user', json=jsonCreateUser)

		jsonLogin = {'username': 'tptaller2', 'password': 'pass'}
		r = requests.post('http://localhost:8080/login', json=jsonLogin)
		jsonResponse = r.json()

		headersCreateFile={'username': jsonResponse["data"]["username"], 'token': jsonResponse["data"]["token"]}
		jsonCreateFile = {'name': 'file1', 'extension': 'jpg', 'idFolder': 'tptaller2', 'labels': [{'description': 'sarasa'}, {'description': 'mas sarasa'}], 'data': 'data111111111111111111'}
		r = requests.post('http://localhost:8080/file', json=jsonCreateFile, headers=headersCreateFile)
		jsonResponse = r.json()
		self.assertEqual("OK", jsonResponse["result"])
		self.assertEqual("file1", jsonResponse["data"]["name"])

	#creacion de carpeta en carpeta root del usuario
	def test_create_folder(self):
		jsonLogin = {'username': 'tptaller2', 'password': 'pass'}
		r = requests.post('http://localhost:8080/login', json=jsonLogin)
		jsonResponse = r.json()

		headersCreateFolder={'username': jsonResponse["data"]["username"], 'token': jsonResponse["data"]["token"]}
		jsonCreateFolder = {'name': 'folder1', 'idParent': 'tptaller2'}
		r = requests.post('http://localhost:8080/folder', json=jsonCreateFolder, headers=headersCreateFolder)
		jsonResponse = r.json()
		self.assertEqual("OK", jsonResponse["result"])
		self.assertEqual("folder1", jsonResponse["data"]["name"])

	#obtencion de carpeta root del usuario
	def test_get_folder(self):
		jsonLogin = {'username': 'tptaller2', 'password': 'pass'}
		r = requests.post('http://localhost:8080/login', json=jsonLogin)
		jsonResponse = r.json()

		headersGetFolder={'username': jsonResponse["data"]["username"], 'token': jsonResponse["data"]["token"]}
		r = requests.get('http://localhost:8080/folder?idFolder=tptaller2', headers=headersGetFolder)
		jsonResponse = r.json()
		self.assertEqual("OK", jsonResponse["result"])
		self.assertEqual("root", jsonResponse["data"]["name"])
		self.assertEqual("file1", jsonResponse["data"]["children"][0]["name"])
		self.assertEqual("folder1", jsonResponse["data"]["children"][1]["name"])

	#obtencion de archivo (metadatos)
	def test_get_file(self):
		jsonLogin = {'username': 'tptaller2', 'password': 'pass'}
		r = requests.post('http://localhost:8080/login', json=jsonLogin)
		jsonResponse = r.json()

		headers={'username': jsonResponse["data"]["username"], 'token': jsonResponse["data"]["token"]}
		r = requests.get('http://localhost:8080/folder?idFolder=tptaller2', headers=headers)
		jsonResponse = r.json()

		r = requests.get('http://localhost:8080/file?idFile='+jsonResponse["data"]["children"][0]["id"], headers=headers)
		jsonResponse = r.json()
		self.assertEqual("OK", jsonResponse["result"])
		self.assertEqual("file1", jsonResponse["data"]["name"])
		self.assertEqual("jpg", jsonResponse["data"]["extension"])
		self.assertEqual("sarasa", jsonResponse["data"]["labels"][0]["description"])
		self.assertEqual("mas sarasa", jsonResponse["data"]["labels"][1]["description"])

	#obtencion de archivo (fisico)
	def test_get_file_data(self):
		jsonLogin = {'username': 'tptaller2', 'password': 'pass'}
		r = requests.post('http://localhost:8080/login', json=jsonLogin)
		jsonResponse = r.json()

		headers={'username': jsonResponse["data"]["username"], 'token': jsonResponse["data"]["token"]}
		r = requests.get('http://localhost:8080/folder?idFolder=tptaller2', headers=headers)
		jsonResponse = r.json()

		r = requests.get('http://localhost:8080/file?idFile='+jsonResponse["data"]["children"][0]["id"]+'&version=1', headers=headers)
		jsonResponse = r.json()
		self.assertEqual("OK", jsonResponse["result"])
		self.assertEqual("data111111111111111111", jsonResponse["data"]["data"])

	#actualizacion de archivo (fisico)
	def test_update_file_data(self):
		jsonLogin = {'username': 'tptaller2', 'password': 'pass'}
		r = requests.post('http://localhost:8080/login', json=jsonLogin)
		jsonResponse = r.json()

		headers={'username': jsonResponse["data"]["username"], 'token': jsonResponse["data"]["token"]}
		r = requests.get('http://localhost:8080/folder?idFolder=tptaller2', headers=headers)
		jsonResponseGetFolder = r.json()

		jsonUpdateFile = {'data': '222'}
		r = requests.put('http://localhost:8080/file?idFile='+jsonResponseGetFolder["data"]["children"][0]["id"], json=jsonUpdateFile, headers=headers)
		jsonResponse = r.json()
		self.assertEqual("OK", jsonResponse["result"])
		self.assertEqual(2, jsonResponse["data"]["version"])

		r = requests.get('http://localhost:8080/file?idFile='+jsonResponseGetFolder["data"]["children"][0]["id"]+'&version=2', headers=headers)
		jsonResponse = r.json()
		self.assertEqual("OK", jsonResponse["result"])
		self.assertEqual("222", jsonResponse["data"]["data"])

	#borrado de carpeta
	def test_delete_folder(self):
		jsonLogin = {'username': 'tptaller2', 'password': 'pass'}
		r = requests.post('http://localhost:8080/login', json=jsonLogin)
		jsonResponse = r.json()

		headers={'username': jsonResponse["data"]["username"], 'token': jsonResponse["data"]["token"]}
		jsonCreateFolder = {'name': 'folder2', 'idParent': 'tptaller2'}
		requests.post('http://localhost:8080/folder', json=jsonCreateFolder, headers=headers)

		r = requests.delete('http://localhost:8080/folder?idFolder=tptaller2/folder2', headers=headers)
		jsonResponse = r.json()
		self.assertEqual("OK", jsonResponse["result"])

	#borrado de archivo
	def test_delete_file(self):
		jsonLogin = {'username': 'tptaller2', 'password': 'pass'}
		r = requests.post('http://localhost:8080/login', json=jsonLogin)
		jsonResponse = r.json()

		headers={'username': jsonResponse["data"]["username"], 'token': jsonResponse["data"]["token"]}
		jsonCreateFile = {'name': 'file2', 'extension': 'txt', 'idFolder': 'tptaller2/folder1', 'labels': [{'description': 'qwerty'}], 'data': 'datos y mas datos'}
		requests.post('http://localhost:8080/file', json=jsonCreateFile, headers=headers)

		r = requests.get('http://localhost:8080/folder?idFolder=tptaller2/folder1', headers=headers)
		jsonResponseGetFolder = r.json()

		r = requests.delete('http://localhost:8080/file?idFile='+jsonResponseGetFolder["data"]["children"][0]["id"], headers=headers)
		jsonResponseDeleteFolder = r.json()
		self.assertEqual("OK", jsonResponseDeleteFolder["result"])

		r = requests.get('http://localhost:8080/folder?idFolder=trash_tptaller2', headers=headers)
		jsonResponseGetFolder = r.json()
		self.assertEqual("file2", jsonResponseGetFolder["data"]["children"][0]["name"])

	#update de archivo (modifico metadatos y recupero archivo borrado)
	def test_update_file_recovering(self):
		jsonLogin = {'username': 'tptaller2', 'password': 'pass'}
		r = requests.post('http://localhost:8080/login', json=jsonLogin)
		jsonResponse = r.json()

		headers={'username': jsonResponse["data"]["username"], 'token': jsonResponse["data"]["token"]}
		r = requests.get('http://localhost:8080/folder?idFolder=trash_tptaller2', headers=headers)
		jsonResponseGetFolder = r.json()
		self.assertEqual("file2", jsonResponseGetFolder["data"]["children"][0]["name"])

		jsonUpdateFile = {'name': 'file2_renombrado', 'extension': 'gif', 'labels': '', 'users': '', 'deleted': False}
		r = requests.put('http://localhost:8080/file?idFile='+jsonResponseGetFolder["data"]["children"][0]["id"], json=jsonUpdateFile, headers=headers)
		jsonResponseUpdateFile = r.json()
		self.assertEqual("OK", jsonResponseUpdateFile["result"])
		self.assertEqual("file2_renombrado", jsonResponseUpdateFile["data"]["name"])

		r = requests.get('http://localhost:8080/folder?idFolder=recovered_tptaller2', headers=headers)
		jsonResponseGetFolder = r.json()
		self.assertEqual("file2_renombrado", jsonResponseGetFolder["data"]["children"][0]["name"])

	#update de archivo (comparto archivo)
	def test_update_file_sharing(self):
		jsonLogin = {'username': 'tptaller2', 'password': 'pass'}
		r = requests.post('http://localhost:8080/login', json=jsonLogin)
		jsonResponse = r.json()

		headers={'username': jsonResponse["data"]["username"], 'token': jsonResponse["data"]["token"]}
		r = requests.get('http://localhost:8080/folder?idFolder=recovered_tptaller2', headers=headers)
		jsonResponseGetFolder = r.json()
		jsonUpdateFile = {'name': 'file2_renombrado', 'extension': 'gif', 'labels': '', 'users': [{'username': 'juanperez'}], 'deleted': False}
		requests.put('http://localhost:8080/file?idFile='+jsonResponseGetFolder["data"]["children"][0]["id"], json=jsonUpdateFile, headers=headers)


		jsonLogin = {'username': 'juanperez', 'password': 'juanperez'}
		r = requests.post('http://localhost:8080/login', json=jsonLogin)
		jsonResponse = r.json()
		headers = {'username': jsonResponse["data"]["username"], 'token': jsonResponse["data"]["token"]}
		r = requests.get('http://localhost:8080/folder?idFolder=sharedwith_juanperez', headers=headers)
		jsonResponseGetFolder = r.json()
		self.assertEqual("file2_renombrado", jsonResponseGetFolder["data"]["children"][0]["name"])


if __name__ == '__main__':
	suite = unittest.TestLoader().loadTestsFromTestCase(TestRequests)
	unittest.TextTestRunner(verbosity=2).run(suite)
