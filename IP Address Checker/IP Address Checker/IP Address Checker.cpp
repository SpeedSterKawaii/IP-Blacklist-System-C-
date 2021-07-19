#include <Windows.h>
#include <string>
#include <iostream>
#include <WinInet.h>
#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib, "wininet.lib")

std::string replaceAll(std::string subject, const std::string& search,
	const std::string& replace) {
	size_t pos = 0;
	while ((pos = subject.find(search, pos)) != std::string::npos) {
		subject.replace(pos, search.length(), replace);
		pos += replace.length();
	}
	return subject;
}

std::string DownloadURL(const char* URL) {
	HINTERNET interwebs = InternetOpenA("Mozilla/5.0", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, NULL);
	HINTERNET urlFile;
	std::string rtn;
	if (interwebs) {
		urlFile = InternetOpenUrlA(interwebs, URL, NULL, NULL, NULL, NULL);
		if (urlFile) {
			char buffer[2000];
			DWORD bytesRead;
			do {
				InternetReadFile(urlFile, buffer, 2000, &bytesRead);
				rtn.append(buffer, bytesRead);
				memset(buffer, 0, 2000);
			} while (bytesRead);
			InternetCloseHandle(interwebs);
			InternetCloseHandle(urlFile);
			std::string p = replaceAll(rtn, "|n", "\r\n");
			return p;
		}
	}
	InternetCloseHandle(interwebs);
	std::string p = replaceAll(rtn, "|n", "\r\n");
	return p;
}

// IP Checker System n Stuff (credit SpeedSterKawaii if using) \\

std::string IP = DownloadURL("http://ipv4bot.whatismyipaddress.com/");
std::string Blacklisted = "66.115.181.202"; // Not my original ip cant ddos :smirk:

int main()
{
    SetConsoleTitleA("IP Address Checker // SpeedSterKawaii");
    std::cout << "Welcome to the IP Address Checker" << std::endl;
    std::cout << "Your IP Address is " << IP << std::endl; // First show the IP.
	std::cout << "Check if your IP is Blacklisted" << std::endl;

	if (IP == Blacklisted) // If IP matches the blacklisted.
	{
		std::cout << "Sorry, but your blacklisted!" << std::endl;
	}
	else
	{
		std::cout << "You should be whitelisted." << std::endl;
	}

	while (true) {} // Stops the console from automatically closing.
}