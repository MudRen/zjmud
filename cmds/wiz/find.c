// find.c 

#include <ansi.h>

// ENABLE_BAR ģʽ����� hell �� MUD�����ṩ�� process_bar()
// ��� simul_efun �� attack_system(),detach_system() ������
// ������ USER_OB �ĺ������������� ANSI ���Ʒ�����ʾ������һ
// Щ�Ľ�������ʱ����Ϊ 1 ���ɡ�
#define ENABLE_BAR      0

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

public void search_dir(object me, string file, string dir, int raw);
public void search_in_file(object me, string info, string file);
public string *search_file(string file, string *flist, object me, int raw);
public string *deep_file_list(string dir);

int main(object me, string arg)
{
	string file, dir, flag;
	int raw;
	
	// Ȩ�޼�飬��Ҫ��ȫϵͳ֧��
	if (! SECURITY_D->valid_grant(me, "(arch)"))
		return 0;
		
	if (! arg)
		return notify_fail("ָ���ʽ��find <�ļ���|����> in <Ŀ¼��|�ļ���> [-c]\n");

	if (sscanf(arg, "%s in %s %s", file, dir, flag) != 3)
	{
		if (sscanf(arg, "%s in %s", file, dir) != 2)
			notify_fail("ָ���ʽ��find <�ļ���|����> in <Ŀ¼��|�ļ���> [-c]\n");
	}

	// ����ǲ��Ұ�������ģʽ
	if (flag == "-c") raw = 1;

	dir = resolve_path(me->query("cwd"), dir);
	
	seteuid(getuid(me));
	
	// ��������ļ��в���ģʽ
	if (file_size(dir) >= 0)
	{
		search_in_file(me, file, dir);
		return 1;
	}
	
	if (file_size(dir) == -2 && dir[strlen(dir) - 1] != '/') dir += "/";
	if (file_size(dir) != -2) 
		return notify_fail(dir + " ������һ��Ŀ¼��\n");
	
	// ��һ����ʾ����Ϊ��ҿ��ܻ���ڳ���
	message_system("ϵͳ�������ݴ����У������ĵȺ�...");
	
#if ENABLE_BAR 
	write(HIR "\n����ϵͳ�������� " + dir + " Ŀ¼���Ժ�㱨��"NOR"\n"
	      HIW "���ȣ�" + process_bar(0) + "\n");
	if (me)
	{
		me->attach_system();
		me->write_prompt();
	}
#endif
	search_dir(me, file, dir, raw);
	return 1;
}

void search_dir(object me, string file, string dir, int raw)
{
	string *flist, *result;
	string info;
	
	// ������е����Ŀ¼�ļ��б�
	flist = deep_file_list(dir);
	
	if (! arrayp(flist) || ! sizeof(flist))
	{
		message_system("ϵͳ���ݴ�����ϣ��������Ϸ��\n" ESC + "[K");
		info = HIR "�ļ�������ϣ�"NOR"\n" ESC + "[K"
		       HIR "Ŀ¼ " + dir + " �²�û�пɹ����ҵ��ļ���" NOR;
		
		message("system", info, me);
#if ENABLE_BAR
		me->detach_system();
#endif
		return;
	}

	result = search_file(file, flist, me, raw);
	
#if ENABLE_BAR
	me->detach_system();
#endif

	message_system("ϵͳ���ݴ�����ϣ��������Ϸ��\n" ESC + "[K");
		
	if (! sizeof(result))
		info = HIR "�ļ�������ϣ�\n" + ESC + "[K" + ""NOR"\n" ESC + "[K"
		       HIR "Ŀ¼ " + dir + " ��û���ҵ��κη���Ҫ����ļ���"NOR"\n"
		       ESC + "[K";

	else 
	{
		info = HIR "�ļ�������ϣ�\n" + ESC + "[K" + ""NOR"\n" ESC + "[K" + 
		       CYN + implode(result, "\n") + NOR + ESC + "[K"
		       HIR "\n\nһ���ҵ� " + sizeof(result) + " ���ļ���" + ESC + "[K" + NOR
		       ESC + "[K\n" + ESC + "[K";
	}
	
	if (me)
		me->start_more(info);
}

string *deep_file_list(string dir)
{
	int i;
	string *flist, *result = ({ }), file;
	
	flist = get_dir(dir);
	
	for (i = 0; i < sizeof(flist); i++)
	{
		file = dir + flist[i];
		
		if (file_size(file + "/") == -2)
			result += deep_file_list(file + "/");
		else 
			result += ({ file });
	}
	
	return result;
}

string *search_file(string file, string *flist, object me, int raw)
{
	int i, j;
	string *result = ({ }), file_info;

	for (i = 0; i < sizeof(flist); i++)
	{
		if (! (i % 100)) reset_eval_cost();
#if ENABLE_BAR
		message("system", NOR ESC + "[1A" + ESC + "[256D"
				  HIG "���ȣ�" + process_bar((i + 1) * 100 / sizeof(flist)) +
				  "\n" + ESC + "[K", me);
#endif
		if (raw == 0)
		{
			j = strsrch(flist[i], "/", -1);
			file_info = flist[i][j..(sizeof(flist[i]) - 1)];
		
			if (file_info == file)
			{
				result += ({ flist[i] });
				continue;
			}
			if (strsrch(file_info, file) > -1)
			{
				result += ({ flist[i] });
				continue;
			}
		}
		else
		{
			// ����ļ�����û�����Ҫ�ҵ��ַ�����
			if (file_size(flist[i]) < strlen(file))
				continue;
			
			if (! read_file(flist[i]))
				continue;
			
			if (strsrch(read_file(flist[i]), file) > -1)
			{
				result += ({ flist[i] });
				continue;
			}
		}
	}
	return result;
}

void search_in_file(object me, string word, string file)
{
	string text, info;
	string *lines;
	int line, num, i, count = 0;
	
	seteuid(getuid(me));
	if (! text = read_file(file))
	{
		write(HIR "\n�ļ� " + file + " ��ʧ�ܣ���������Ϊ�ļ�����"NOR"\n");
		return;
	}
	
	if (strsrch(text, word) == -1)
	{
		write(HIR "\n�ļ� " + file + " �ڲ����ް�����" HIW + word + 
		      HIR "���ַ�����"NOR"\n");
		return;
	}
	
	lines = explode(text, "\n");
	info = HIR "�����ļ� " + file + " �в��Ұ��� " + word + "\n�ַ��������ݣ�"NOR"\n";
	
	line = sizeof(lines);
	for (i = 0; i < line; i++)
	{
		num = strsrch(lines[i], word);

		if (num > -1)
		{
			info += WHT "�ڵ� " + (i + 1) + " �еĵ� " + (num + 1) + " �ֽڴ�"
				"�ҵ�ָ���ַ���"NOR"\n";

			info += CYN "............"NOR"\n";
			info += (i - 1) >= 0 ? CYN + lines[i - 1] + "\n" + NOR : "";
			info += CYN + replace_string(lines[i], word, WHT + word + CYN) + "\n" + NOR;
			info += (i + 1) < line ? CYN + lines[i + 1] + "\n" + NOR : "";
			info += CYN "............"NOR"\n";
			
			count++;
		}
	}
	info += HIR "��ѯ��ϣ�һ���ҵ� " + count + " �����ϵ����ݡ�" NOR;
	
	me->start_more(info);
	return;
}

int help(object me)
{
	write(@HELP
ָ���ʽ: find <�ļ���|����> in <Ŀ¼��|�ļ���> [-c]
 
����Ŀ¼������Ŀ¼�����а���ָ���ļ������ļ���Ŀ¼�����ҽ����
�صĸ�ʽΪ��<�ļ���> <�ļ���С> <��һ���޸�ʱ��>��
��������� -c �������ʾ������ָ��Ŀ¼�°���ָ�����ݵ��ļ���
���ָ����λ����һ���ļ��������ʾ���Ǹ��ļ��в��Ұ���ָ������
���С�
HELP );
	return 1;
}

