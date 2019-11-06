#pragma once

std::string clear_the_text(std::string data)
{
	std::string data_ptr;

	for (int i = 0; i < data.length(); i++)
	{
		if (data[i] >= 'à' && data[i] <= 'ÿ' || data[i] >= 'À' && data[i] <= 'ß')
		{
			data_ptr += data[i];
		}
	}

	boost::to_lower(data_ptr, std::locale(".1251"));
	boost::replace_all(data_ptr, "¸", "å");
	boost::replace_all(data_ptr, "ú", "ü");

	return data_ptr;
}

std::wstring toUNICODE(void* buffer, int64_t buffer_size)
{
	int64_t unicode_buffer_size = MultiByteToWideChar(CP_UTF8, 0, (LPCCH)buffer, buffer_size, 0, 0) * sizeof(wchar_t) + 2;

	wchar_t* unicode_data_ptr = (wchar_t*)malloc(unicode_buffer_size);
	ZeroMemory(unicode_data_ptr, unicode_buffer_size);

	MultiByteToWideChar(CP_UTF8, 0, (LPCCH)buffer, buffer_size, unicode_data_ptr, unicode_buffer_size);

	std::wstring unicode_wstring(unicode_data_ptr);

	return unicode_wstring;
}

std::string to1251(std::wstring unicode_data)
{
	int64_t mb_buffer_size = WideCharToMultiByte(1251, 0, unicode_data.c_str(), unicode_data.length(), 0, 0, 0, 0) + 1;

	char* mb_data_ptr = (char*)malloc(mb_buffer_size);
	ZeroMemory(mb_data_ptr, mb_buffer_size);

	WideCharToMultiByte(1251, 0, unicode_data.c_str(), unicode_data.length(), mb_data_ptr, mb_buffer_size, 0, 0);

	std::string mb_string(mb_data_ptr);

	return mb_string;
}