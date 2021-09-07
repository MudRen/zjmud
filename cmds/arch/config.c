// config.c

#include <ansi.h>
#include <runtime_config.h>

inherit F_CLEAN_UP;

void write_config();
string trim(string str);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
	string key;
	mixed val;
	object ob;
	mapping dbase;
	string *cfg;
	string remember;
	string msg;
	string affix;
	int len;

	if (! SECURITY_D->valid_grant(me, "(arch)"))
		return 0;

	if (! arg) arg = "";

	if (sscanf(arg, "-d %s", key) == 1)
	{
		key = trim(key);

		if (undefinedp(CONFIG_D->query(key)))
		{
			write("����������û�� " + key + " ���������\n");
			return 1;
		}

		CONFIG_D->delete(key);
		write("ȥ���˲�����" + key + "��\n");
		return 1;
	}

	if (sscanf(arg, "%s=%s", key, val) == 2)
	{
		// ȥ��key/val���˵Ŀո�
		key = trim(key);
		val = trim(val);

		if ((len = strsrch(val, '#')) != -1)
		{
			// ��βע
			affix = val[len..<1];
			val = val[0..len - 1];
			val = trim(val);
		} else
			affix = 0;

		// ȥ��""
		sscanf(val, "\"%s\"", val);
		if (strlen(val) < 1)
		{
			write("��û��ָ�����������ֵ�������Ҫɾ���Ļ����� -d ѡ�\n");      
			return 1;
		}

		if (! undefinedp(CONFIG_D->query(key)) &&
		    intp(CONFIG_D->query(key)))
			// ԭ�Ȳ�����ֵ������
			if (! sscanf(val, "%d", val))
				write("ע�⣺ԭ�� " + key + " ʹ�õ�������ֵ���������ͱ仯�ˡ�\n");

		write(sprintf("���������� %s ����Ϊ %O��\n", key, val));
		CONFIG_D->set(key, val);
		if (stringp(affix))
			CONFIG_D->set_temp("affix/" + key, affix);

		return 1;
	}

	if (arg == "-w")
	{
		write_config();
		return 1;
	}

	if (arg == "-r")
	{
		// ���¶�ȡ����
		write("���¶�ȡ�����е����ò�����\n\n");
		if (objectp(ob = find_object(CONFIG_D)))
		{
			destruct(ob);
			call_other(CONFIG_D, "???");
		}
		return 1;
	}

	msg = "";
	msg += "Mud ���ƣ�\t\t" + get_config(__MUD_NAME__) + "\n"; 
	msg += "��·��ַ�����ŷ������ţ�" + get_config(__ADDR_SERVER_IP__) + "\n"; 
	msg += "Mudlib ·����\t\t" + get_config(__MUD_LIB_DIR__) + "\n"; 
	msg += "MudOS ִ�е�·����\t" + get_config(__BIN_DIR__) + "\n\n"; 

	dbase = CONFIG_D->query_entire_dbase();
	if (! mapp(dbase))
	{
		write(msg + "����û���κ������е����ò�����\n");
		return 1;
	}

	msg += "����ϵͳ���������ò�����\n";
	cfg = keys(dbase);
	cfg = filter_array(cfg, (: stringp($(dbase)[$1]) || intp($(dbase)[$1]) :));
	if (stringp(arg) && strlen(arg))
	{
		// Ѱ��ƥ��Ĳ���
		cfg = filter_array(cfg, (: strsrch($1, $(arg)) != -1 :));
		if (! sizeof(cfg))
		{
			write(msg + "����û���κο��Ժ� " + arg +
			      " ƥ������ò�����\n");
			return 1;
		}
	}

	cfg = sort_array(cfg, 1);
	foreach (key in cfg)
	{
		if (stringp(remember = CONFIG_D->query_remember(key)))
			msg += CYN + remember + NOR "\n";
		if (! stringp(affix = CONFIG_D->query_affix(key)))
			affix = "";
		msg += sprintf("%-20s: " WHT "%-25O" NOR "%-15s\n",
			       key, dbase[key], CYN + affix + NOR);
	}
	msg += NOR;

	write(msg);
	return 1;
}

// д�ز���
void write_config()
{
	string *tmp, file;
	string line;
	string arg, value;
	string affix;
	mapping dbase;
	string *cfg;
	int len;
	int i;

	// ȡ��ǰ���еĲ���
	if (! mapp(dbase = CONFIG_D->query_entire_dbase()))
		dbase = ([ ]);
	cfg = keys(dbase);
	cfg = filter_array(cfg, (: stringp($(dbase)[$1]) || intp($(dbase)[$1]) :));

	// ��ȡ�����ļ�
	file = read_file(CONFIG_D->query_config_file_name());
	if (! stringp(file))
		file = "";

	// ȥ��"\r"��֤��MSDOS���ļ���ʽ����
	file = replace_string(file, "\r", "");

	tmp = explode(file, "\n");

	// ȥ�����Ŀ���
	while (sizeof(tmp) && tmp[sizeof(tmp) - 1] == "")
		tmp = tmp[0..<2];

	for (i = 0; i < sizeof(tmp); i++)
	{
		line = tmp[i];

		// ȥ�����׵Ŀո�
		while (strlen(line) && line[0] == ' ') line = line[1..<1];
		if (line[0] == '#')
			continue;

		if (line[0] == '&')
		{
			// ��ϵͳע�͵�
			line = line[1..<1];
			while (strlen(line) && line[0] == ' ') line = line[1..<1];
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
			continue;

		// ȥ��argĩβ�Ŀո�
		while ((len = strlen(arg)) > 0 && arg[len - 1] == ' ')
			arg = arg[0..<2];

		// ��������
		value = dbase[arg];

		if (stringp(value))
			line = sprintf("%s : %s", arg, value);
		else
		if (undefinedp(value) || ! intp(value))
			line = "& " + line;
		else
			line = sprintf("%s : %d", arg, value);

		cfg -= ({ arg });

		// ����βע
		if (stringp(affix))
			line = sprintf("%-44s %s", line, affix);

		tmp[i] = line;
	}

	tmp += ({ "" });
	foreach (arg in cfg)
	{
		value = dbase[arg];

		if (stringp(value))
			line = sprintf("%s : %s", arg, value);
		else
		if (intp(value))
			line = sprintf("%s : %d", arg, value);
		else
			continue;
		tmp += ({ line });
	}

	file = implode(tmp, "\n") + "\n";
	write_file(CONFIG_D->query_config_file_name(), file, 1);
	write("������д�ص������ļ��С�\n");
}

// ȥ��str���˵Ŀո�
string trim(string str)
{
	int len;

	// ȥ��str���˵Ŀո�
	while (str[0] == ' ') str = str[1..<1];
	while ((len = strlen(str) - 1) >= 0 && str[len] == ' ')
		str = str[0..<2];

	return str;
}

int help(object me)
{
	write(@HELP
ָ���ʽ : config [-r | -w] | [<������>=<ֵ>] | [-d <������>]

Show ���� MUD �� Startup Configuration ��������Ӳ�����ͬʱ
��ʾ�������е�����(/adm/etc/config)��

-r �������¶�ȡ�����е����á�
-w ��������д�������е����á�
-d ����ȥ��һ�������

HELP );
	return 1;
}
