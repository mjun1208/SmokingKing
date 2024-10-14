#include "DXUT.h"
#include "cScene.h"
#include "cThreadPoolManager.h"
class cLoadScene : public cScene
{
private:
	int NowLoad;
	int MaxLoad;

	int NowOBJLoad;
	int MaxOBJLoad;

	struct strBun
	{
		string key;
		string path;
		int count;

		strBun(const string& key, const string& path, int count = 0)
			:key(key), path(path), count(count) {};
	};

	struct OBJstrBun
	{
		string key;
		string path;
		string mappath;
		string mtlpath;
		int count;

		OBJstrBun(const string& key, const string& path, const string& mappath = "None", int count = 0, const string& mtlpath = "None")
			:key(key), path(path), mappath(mappath), count(count), mtlpath(mtlpath) {};
	};

	vector<OBJstrBun> m_OBJLoad;
	vector<strBun> m_Load;
	void Load(const string& key, const string& path, int count = 0) {
		m_Load.push_back(strBun(key, path, count));
	}
	void OBJLoad(const string& key, const string& path, const string& mappath = "None", int count = 0, const string& mtlpath = "None") {
		m_OBJLoad.push_back(OBJstrBun(key, path,mappath, count, mtlpath));
	}

	//vector<thread> workers;
	//
	//void func1(int A);
	//
	//mutex Mutex;
	//void ThreadLoad(int A, int B, mutex& m);

	///////////////
	cThreadPoolManager Thread;
	std::vector<std::future<int>> futures;
	int ThreadLoadOBJ(int NowCount);
public:
	cLoadScene();
	virtual ~cLoadScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};
