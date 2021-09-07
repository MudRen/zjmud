// emote.c (Mon  09-04-95)

#include <ansi.h>

inherit F_CLEAN_UP;
 
int main(object me, string str)
{
	string *emotes,prefix,estr;
	object env;
	mixed info;
	int i;

	if (me->ban_say())
		return 0;

	env = environment(me);
	if (info = env->query("no_say"))
	{
		if (stringp(info))
		{
			write(info);
			return 1;
		}

		write("����ط���������������\n");
		return 1;
	}

	if (! str)
	{
		emotes = EMOTE_D->query_all_emote();
		estr = ZJOBLONG+"��ǰƵ����"+me->query_temp("pindao/name")+"������ѡ����鶯����\n"ZJOBACTS2+ZJMENUF(3,3,8,30);
//		for(i=0;i<sizeof(emotes);i++)
		for(i=0;i<10;i++)
		{
			estr += emotes[i]+":"+me->query_temp("pindao/id")+"* "+emotes[i]+ZJSEP;
		}
		write(estr+"\n");
		return 1;
	}

	prefix = me->query("env/no_prefix") ? "" : "��";
	write(CYN "��" + str + ""NOR"\n");
	tell_room(env, CYN + prefix + (string)me->name() +  str + ""NOR"\n", me);
	return 1;
}
 
int help(object me)
{
	write(@HELP
ָ���ʽ: emote <������>

���ָ�����������һ��ϵͳû��Ԥ��Ķ�����, ϵͳ�Ὣ��������
�����ּ��������������ʾ��������ͬһ���ط������￴��Ϊ�˱�����
������, ���������Ĵʾ�ǰ������ ~ �Թ�����

����: emote ����������
��ῴ��: ������������
�����˻ῴ��: ~��������������

����, ���Ӿ����������.

���ָ��: semote
HELP );
	return 1;
}
