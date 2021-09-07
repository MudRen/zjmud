// hatred.c

#include <ansi.h>

inherit F_CLEAN_UP;

// Ϊ���еĳ�޶������򣺽���
int sort_hatred(string id1, string id2, mapping hatred)
{
	mixed *d1, *d2;

	if (! arrayp(d1 = hatred[id1]) || sizeof(d1) < 2 || ! intp(d1[1]))
		return 1;

	if (! arrayp(d2 = hatred[id2]) || sizeof(d2) < 2 || ! intp(d2[1]))
		return -1;

	return d2[1] - d1[1];
}

int main(object me, string arg)
{
	object ob;
	mapping hatred;
	string fam;
	string *ids;
	mixed *data;
	string msg;
	string st;
	int count;
	int i;

	if (! wizardp(me))
		// only wizard can show every family's list
		fam = 0;
	else
	if (stringp(arg))
	{
		fam = FAMILY_D->query_family_name(arg);
		if (strlen(fam) < 2 || fam[0] < 160)
			// ��������������֣�����ζ��û�л�ȷ������
			fam = 0;

		if (! stringp(fam) && objectp(ob = find_player(arg)))
		{
			// û�� arg ������ɣ��鿴�Ƿ��и����
			fam = ob->query("family/family_name");
			if (! stringp(fam))
				return notify_fail(ob->name(1) +
						   "����û�м����κ����ɡ�\n");
		}

		if (! stringp(fam))
			return notify_fail("û�������ң����ܲ�����ص����ɡ�\n");
	}

	if (! fam)
	{
		// select my family
		if (! stringp(fam = me->query("family/family_name")))
			return notify_fail("�����ڻ�û�м���һ�������ء�\n");
	}

	hatred = FAMILY_D->query_family_hatred(fam);
	if (! mapp(hatred) || ! sizeof(hatred))
		return notify_fail(fam + "����û��ʲô���ˡ�\n");

	ids = keys(hatred) - ({ 0 });
	ids = sort_array(ids, (: sort_hatred :), hatred);

	count = 0;
	msg = WHT "Ŀǰ" + fam + "�ڽ����ϵĳ�ж���"NOR"\n"
	      HIY "��������������������������������"NOR"\n";
	for (i = 0; i < sizeof(ids) && count < 30; i++)
	{
		data = hatred[ids[i]];
		if (! arrayp(data) || sizeof(data) < 2 ||
		    ! stringp(data[0]) || ! intp(data[1]))
			continue;

		st = sprintf("%s(%s%s%s)", data[0], YEL, ids[i], NOR);
		msg += sprintf("%2d. %-34s  %s%-9d%s\n",
			       ++count, st, HIR, data[1], NOR);
	}

	msg += HIY "��������������������������������"NOR"\n";
	if (i < sizeof(ids))
		msg += WHT "�����ϵĵ���̫�࣬���Ծ�����"NOR"\n";
	else
		msg += WHT "Ŀǰһ����" + chinese_number(i) +
		       "�ˡ�"NOR"\n";
	write(msg);
	return 1;
}

int help(object me)
{
   	write(@HELP
ָ���ʽ: hatred

�鿴Ŀǰ�����������ɵ�ʹ�޶�����ʦ���Բ鿴�κ����ɵ�ʹ�޶�
��ֻ����ָ����ָ����ص����ɻ��������е���ҡ�
HELP );
   	return 1;
}
