#include <QtCore/QCoreApplication>
#include <qt_windows.h>

int main(int argc, char* argv[])
{
	QCoreApplication a(argc, argv);
	DWORD dwordPidOld{ 0 };
	qint16 countCirculate{ 0 };
	bool flagMessage{ true };
	while (countCirculate < 6 && flagMessage)
	{
		HWND wid = FindWindow(NULL, L"远程桌面连接");
		if (wid)
		{
			DWORD dwordPidNew = GetWindowThreadProcessId(wid, NULL);
			if (dwordPidOld == 0)
			{
				dwordPidOld = dwordPidNew;
			}
			if (dwordPidOld == dwordPidNew)
			{
				if (countCirculate >= 5)
				{
					MessageBox(NULL, L"该关闭远程桌面了", L"该关闭远程桌面了", NULL);
					HWND hwndNew = FindWindow(NULL, L"远程桌面连接");
					while (hwndNew)
					{
						Sleep(60000);
						hwndNew = FindWindow(NULL, L"远程桌面连接");
						if (hwndNew)
						{
							MessageBox(NULL, L"该关闭远程桌面了", L"该关闭远程桌面了", NULL);
						}
						hwndNew = FindWindow(NULL, L"远程桌面连接");

					}
					flagMessage = false;
				}
			}
			else
			{
				countCirculate = 0;
			}
		}
		else
		{
			countCirculate = 0;
		}
		Sleep(60000);
		++countCirculate;
	}
	exit(0);
	return a.exec();
}
