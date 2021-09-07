#include <runtime_config.h>

#pragma optimize
#pragma save_binary

inherit F_DBASE;

#define CONFIG_FILE     CONFIG_DIR "config"

// �����ļ��в����ĸ�ʽ�ǣ�  arg : value
// �����#��ͷ��ʾע�ͣ�&��ͷ��ʾ��ϵͳע�͵ġ�

void load_config();

void create()
{
	seteuid(getuid());
	load_config();
}

void load_config()
{
	string *tmp, file;
	string line;
	string arg, value;
	string last_remember;
	string affix;
	int len;
	int sys_del;

	file = read_file(CONFIG_FILE);
	if (! stringp(file)) return;

	// ȥ��"\r"��֤��MSDOS���ļ���ʽ����
	file = replace_string(file, "\r", "");

	sys_del = 0;
	tmp = explode(file, "\n");
	foreach (line in tmp)
	{
		if (sys_del)
		{
			// ��һ�������Ǳ�ϵͳע�͵���
			last_remember = 0;
			sys_del = 0;
		}

		// ȥ�����׵Ŀո�
		while (strlen(line) && line[0] == ' ') line = line[1..<1];
		if (line[0] == '#')
		{
			// ע��
			last_remember = line;
			continue;
		}

		if (line[0] == '&')
		{
			// ��ϵͳע�͵�
			line = line[1..<1];
			while (strlen(line) && line[0] == ' ') line = line[1..<1];
			sys_del = 1;
		}

		// ȥ��#�Ժ����е��ַ�
		len = strsrch(line, '#');
		if (len != -1)
		{
			// ��¼βע
			affix = line[len..<1];
			line = line[0..len - 1];
		} else
			affix = 0;

		if (! strlen(line))
			continue;

		// ������
		if (sscanf(line, "%s:%s", arg, value) != 2)
		{
			log_file("config", sprintf("syntax error: <%s>\n", line));
			continue;
		}

		// ȥ��argĩβ�Ŀո�
		while ((len = strlen(arg)) > 0 && arg[len - 1] == ' ')
			arg = arg[0..<2];

		if (! strlen(arg))
		{
			log_file("config", sprintf("syntax error: <%s>\n", line));
			last_remember = 0;
			continue;
		}

		// ȥ��value��ͷ�Ŀո�
		while (strlen(value) && value[0] == ' ')
			value = value[1..<1];

		// ȥ��valueĩβ�Ŀո�
		while ((len = strlen(value)) > 0 && value[len - 1] == ' ')
			value = value[0..<2];

		if (! sys_del)
		{
			// ϵͳû��ע���������
			set(arg, value);
			sys_del = 0;
		}

		if (stringp(last_remember))
		{
			// �����ע�ͣ������
			set_temp("remember/" + arg, last_remember);
			last_remember = 0;
		}

		if (stringp(affix))
		{
			// �����βע�������
			set_temp("affix/" + arg, affix);
			affix = 0;
		}
	}
}

// ������������
int query_int(string index)
{
	int result;

	if (! intp(result = query(index)))
	{
		// ����INT���͵�ֵ
		if (stringp(result))
			// ���ַ������������ȡֵ
			sscanf(result, "%d", result);
		else
			result = 0;
		set(index, result);
	}

	return result;
}

// �����ַ�������
string query_string(string index)
{
	string result;

	if (! stringp(result = query(index)))
		result = "unknow";

	return result;
}

// ���ز�����ע��
string query_remember(string index)
{
	return query_temp("remember/" + index);
}

// ���ز�����βע
string query_affix(string index)
{
	return query_temp("affix/" + index);
}

// ���������ļ�������
string query_config_file_name() { return CONFIG_FILE; }
