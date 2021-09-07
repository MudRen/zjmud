// system.c

#include <ansi.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

string fs(int supplied);
string fc(int cost);
void   show_update_info(string arg);

int main(object me, string arg)
{
	string msg;
	mapping cm;

	if (arg && sscanf(arg, "-ui%s", arg))
	{
		show_update_info(arg);
		return 1;
	}

	cm = COMBAT_D->query_entire_dbase();
	msg = "ϵͳ���ڵ����ã�\n";
	if (! mapp(cm))
		msg += "���顣\n\n";
	else
		msg += "PK �������ƣ�ÿ�첻���� " HIR +
		       cm["pk_perday"] + NOR " �ˣ�ÿ�˲����� "
		       HIR + cm["pk_perman"] + NOR + " �Ρ�\n\n";

	cm = CPU_D->query_entire_dbase();
	msg += "���һ��ʱ��ϵͳʹ��CPU�����ͳ�ƣ�\n";
	msg += "ϵͳ�ṩCPU��Դ������ȣ�" + fs(cm["last_0"]["supplied"]) +
	      "  ��Ϸ��CPU��ռ���ʣ�" + fc(cm["last_0"]["cost"]) + "��\n";

	msg += sprintf("ǰһЩʱ��CPU������Ⱥ�ռ���ʣ�%s/%s  %s/%s  %s/%s  %s/%s��\n",
		       fs(cm["last_1"]["supplied"]), fc(cm["last_1"]["cost"]),
		       fs(cm["last_2"]["supplied"]), fc(cm["last_2"]["cost"]),
		       fs(cm["last_3"]["supplied"]), fc(cm["last_3"]["cost"]),
		       fs(cm["last_4"]["supplied"]), fc(cm["last_4"]["cost"]));
	write(msg);
	return 1;
}

string fs(int supplied)
{
	if (supplied <= 70)
		return sprintf(RED "%d%%" NOR, supplied);
	else
	if (supplied <= 90)
		return sprintf(HIR "%d%%" NOR, supplied);

	return sprintf(WHT "%d%%" NOR, supplied);
}

string fc(int cost)
{
	if (cost >= 90)
		return sprintf(RED "%d%%" NOR, cost);
	else
	if (cost >= 70)
		return sprintf(HIR "%d%%" NOR, cost);

	return sprintf(WHT "%d%%" NOR, cost);
}

void show_update_info(string arg)
{
	mapping pri;
	string *fnames;
	string fname;
	string msg;
	int    count;

	pri = NEWS_D->query_family_priority();

	if (! mapp(pri))
	{
		write("û�����ɵĸ������ȼ���Ϣ������� NEWS_D��\n");
		return;
	}

	sscanf(arg, " %s", arg);
	if (sscanf(arg, "- %s %d", fname, count) == 2 ||
	    sscanf(arg, "-%s %d", fname, count) == 2)
		count = -count;

	if (sscanf(arg, "+ %s %d", fname, count) == 2||
	    sscanf(arg, "+%s %d", fname, count) == 2)
		;

	if (VERSION_D->is_release_server() && count != 0)
	{
		if (! SECURITY_D->valid_grant(this_player(), "(admin)"))
		{
			write("��û��Ȩ�޵������ɸ��µ����ȼ����á�\n");
			return;
		}

		if (undefinedp(pri[fname]))
		{
			write("û��������ɡ�\n");
			return;
		}

		pri[fname] += count;
		write("������" + FAMILY_D->query_family_name(fname) +
		      "�����ȼ����仯������" WHT + count + NOR "��\n");
		NEWS_D->save();
		return;
	}

	msg = "Ŀǰ���ɵĸ������ȼ���\n";
	fnames = sort_array(keys(pri), (: $(pri)[$2] - $(pri)[$1] :));
	foreach (fname in fnames)
	{
		msg += sprintf("%-8s  %d\n",
			       FAMILY_D->query_family_name(fname),
			       pri[fname]);
	}
	write(msg);
}

int help(object me)
{
	write(@HELP
ָ���ʽ : system [-ui] [+|- <����> <����>]
 
���ָ�������ʾ��Ŀǰ��Ϸ��ͨ�����ú�ʹ��ϵͳ��Դ��״����ʹ
�� ui �������Բ���Ŀǰ MUD ����߶��ڵ����ɵĸ������ȼ���
 
HELP );
	return 1;
}
