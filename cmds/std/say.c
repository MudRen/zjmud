// say.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object env;
	mixed msg;

	if (me->ban_say(1))
		return 0;

	env = environment(me);
	if (! arg)
	{
		write("���������ﲻ֪����˵Щʲô��\n");
		message("sound", me->name() + "�������ﲻ֪����˵Щʲô��\n",
			env, me);
		return 1;
	}

	if (msg = env->query("no_say"))
	{
		if (stringp(msg))
		{
			write(msg);
			return 1;
		}

		write("����ط����ܽ�����\n");
		return 1;
	}

	write(CYN "��˵����" + arg + ""NOR"\n");
	message("sound", CYN + me->name() + CYN "˵����" +  arg + ""NOR"\n",
		env, me);

	// The mudlib interface of say
	all_inventory(env)->relay_say(me, arg);

	return 1;
}

int help (object me)
{
	write(@HELP
ָ���ʽ: say <ѶϢ>
 
˵�������и�����ͬһ��������˶���������˵�Ļ��������������
auto_say��������ôϵͳ���Զ��Ľ�������ķ�����ͱ��鶯����Ϊ
�㽲�Ļ����������������pure_say��������ô������������ '/'
�ַ���ͷ���������ϵͳ����������˵�Ļ�������
 
ע: ��ָ����� ' ȡ��.
 
HELP
	);
	return 1;
}
