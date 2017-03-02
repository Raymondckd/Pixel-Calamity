#pragma once

class Singleton
{
protected:
	static Singleton* mInstance;

	Singleton() {}
	virtual ~Singleton() {}
public:

	static Singleton* Instance()
	{
		if (!mInstance)
			mInstance = new Singleton();

		return mInstance;
	}
	void Singleton::Destroy()
	{
		delete mInstance;
	}

};
