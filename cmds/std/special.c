// special

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	string  msg;
	mapping ss;
	string  skill;
	object ob;
	string pro;
       
	if (wizardp(me) && stringp(arg) &&
	    objectp(ob = find_player(arg)))
		// �鿴������ҵ����⼼��
		arg = 0;
	else
		ob = me;

	pro = (ob == me) ? "��" : ob->name(1);

	if (! ob->query("born"))
		return notify_fail(pro + "��û�г����ţ���ʲô�ؼ���\n");

	if (! mapp(ss = ob->query("special_skill")) ||
	    ! sizeof(ss))
		return notify_fail(pro + "���ں���ʲô�ؼ�������Ŷ��\n");

	if (arg && (ob == me))
	{
		// �в����������ؼ���
		if (me->is_busy())
			return notify_fail("������æ���أ�����ʹ���ؼ���\n");

		if (sscanf(arg, "%s %s", skill, arg) != 2)
			skill = arg;

		if (! me->query("special_skill/" + skill))
			return notify_fail("�㲻�������ؼ�����\n");

		if (file_size(SPECIAL_D(skill) + ".c") < 0)
			return notify_fail("����û�������ؼ�...\n");

		return SPECIAL_D(skill)->perform(me, skill, arg);
	}

	msg = pro + "���ڻ�������Щ�ؼ���\n";
	foreach (skill in keys(ss))
	{
		if (file_size(SPECIAL_D(skill) + ".c") < 0)
		{
			write("�����ڼ��ܣ�" + skill + "\n");
			continue;
		}
		msg +="  �I"+SPECIAL_D(skill)->name() + "�I(" YEL + skill + NOR ")\n";
	}
	write(msg);
	return 1;
}

int help(object me)
{
write(@HELP
ָ���ʽ : special <skill> | <���ID>

ʹ������������Բ鿴����ؼ������Ҫ��������ؼ�������Լ���
����ָ��ʹ��ʲô�ؼ������磺special hatred������ɱ����

��ʦ���Բ鿴���������������⼼�ܡ�

HELP );
    return 1;
}
