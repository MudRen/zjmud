// secularize.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	if (me->query("class") != "bonze")
		return 0;

	if (stringp(me->query("family/family_name")))
	{
		write("��û������ʦ�����������Ի��ף�\n");
		return 1;
	}

	if (me->query_temp("pending/secularize"))
	{
		CHANNEL_D->do_channel(this_object(), "rumor","��˵" + me->name(1) + "�������ƶ���������������ס�");
		me->delete("class");
		write("���������Դ���̾�˿����������س����ú��������ܡ�\n");

		if (stringp(me->query("purename")))
			me->set_name();
		if (stringp(me->query("purename2")))
			me->set_name();
		return 1;
	}

	me->set_temp("pending/secularize", 1);
	write(YEL "�����Ҫ����������Ǵ��£���������˾��ģ��Ǿ�������һ��������"NOR"\n");
	return 1;
}

int help (object me)
{
	write(@HELP
ָ���ʽ: secularize|huansu
 
���ָ������������ĵĳ������

HELP );
	return 1;
}
