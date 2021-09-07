// ask.c
#include <ansi.h>
inherit F_CLEAN_UP;

string *msg_dunno = ({
	"$nҡҡͷ��˵����û��˵����\n",
	"$n�ɻ�ؿ���$N��ҡ��ҡͷ��\n",
	"$n�����۾�����$N����Ȼ��֪��$P��˵ʲô��\n",
	"$n�����ʼ磬�ܱ�Ǹ��˵���޿ɷ�档\n",
	"$n˵������....���ҿɲ��������������ʱ��˰ɡ�\n",
	"$n����һ�����˵�����Բ������ʵ�����ʵ��û��ӡ��\n"
});

int main(object me, string arg)
{
	string dest, topic, tmpinq, msg;
	object ob;
	mapping inquiry;
	object env;
	mixed info;

	seteuid(getuid());

	if (! arg)
		return notify_fail("��Ҫ��˭ʲô�£�\n");

	if (sscanf(arg, "%s about %s", dest, topic) != 2 &&
	    sscanf(arg, "%s %s", dest, topic) != 2)
		return notify_fail("��Ҫ��˭ʲô�£�\n");

	env = environment(me);
	if (info = env->query("no_say"))
	{
		if (stringp(info))
		{
			write(info);
			return 1;
		}

		write("����ط����ܽ�����\n");
		return 1;
	}

	if (! objectp(ob = present(dest, env)))
		return notify_fail("����û������ˡ�\n");

	if (me->ban_say(1) && playerp(ob))
		return 0;

	if (! ob->is_character())
	{
		message_vision("$N����$n��������....\n", me, ob);
		return 1;
	}

	if (ob == me)
	{
		message_vision("$N�Լ��������\n", me);
		return 1;
	}

	if (me->query("jing") < 30 && ! playerp(ob))
	{
		write("�����ڵľ���̫�ã�û���ͱ����״ɡ�\n");
		return 1;
	}

	if(sscanf(topic,"#%*d-%s",tmpinq)!=2)
		tmpinq = topic;

	if (! ob->query("can_speak"))
	{
		message_vision(CYN "$N" CYN "��$n" CYN 
			       "�����йء�" HIG + topic + NOR CYN "��"
			       "����Ϣ������$p��Ȼ�������˻���"NOR"\n", me, ob);
		return 1;
	}

	if (! INQUIRY_D->parse_inquiry(me, ob, topic))
		message_vision(CYN "$N" CYN "��$n" CYN "�����йء�" HIG +
			       topic + NOR CYN "������Ϣ��"NOR"\n", me, ob);

	if (! living(ob))
	{
		message_vision("���Ǻ���Ȼ�ģ�$n���ڵ�״��û�а취��$N�κδ𸲡�\n",	me, ob);
		return 1;
	}

	if (playerp(ob) || ob->is_chatter())
	{
		ob->set_temp("ask_you", me->query("id"));
		return 1;
	}

	me->receive_damage("jing", 10 + random(10));
	if (msg = ob->query("inquiry/" + topic) || msg = ob->accept_ask(me, topic))
	{
		if (stringp(msg))
		{
			tell_object(me,CYN+ob->query("name")+"˵����" + msg + NOR"\n");
			return 1;
		}
	} else
		message_vision(msg_dunno[random(sizeof(msg_dunno))], me, ob);

	return 1;
}

int help(object me)
{
	write( @HELP
ָ���ʽ: ask <someone> about <something>

���ָ���ڽ���ʱ����Ҫ, ͨ��������ɴ�һָ�����
��ý�һ������Ѷ��
HELP );
	return 1;
}

