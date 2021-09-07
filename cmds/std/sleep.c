// sleep.c

#include <ansi.h>
#include <command.h>

void wakeup(object me);

int main(object me, string arg)
{
	object obj, old_target;
	int i;
	object *inv;
	mapping fam;
	mapping cnd;
	string *kc;
	object where = environment(me);
	int qi, jing;

	seteuid(getuid());

	if ((!(fam = me->query("family")) || fam["family_name"] != "ؤ��")
	     && !(where->query("sleep_room"))
	     || (where->query("no_sleep_room")) )
	     return notify_fail("���ﲻ������˯�ĵط���\n");

	if (me->is_busy())
		return notify_fail("����æ���أ�\n");

	if( me->is_fighting() )
		return notify_fail("ս���в���˯����\n");

	if (where->query("hotel") && !(me->query_temp("rent_paid")))
	{
		message_vision("��С���������$N��У������ﵱ�����������ȵ�һ¥��Ǯ������˯��\n",me);
		return 1;
	}

	jing = (int) me->query("jing");
	qi   = (int) me->query("qi");
	if (jing < 0 || qi < 0)
		return notify_fail("�����ڽӽ����ԣ�˯���ž���\n");
	cnd = me->query_condition();
	if (cnd && sizeof(cnd))
	{
		kc   = keys(cnd);
		for (i = 0; i < sizeof(kc); i++)
		{
			if (CONDITION_D(kc[i])->min_qi_needed(me) > qi ||
			    CONDITION_D(kc[i])->min_jing_needed(me) > jing)
			{
				message("vision", me->name() + "����������˯����"
					"����շת���࣬����˯���š�\n",
					environment(me), me);
				tell_object(me, "��������۾��ú�˯��һ��������" +
					    to_chinese(kc[i]) + "������ĥ���㣬"
					    "����շת���ߡ�\n");
				return 1;
			}
		}
	}

	if (where->query("sleep_room"))
	{
	    write("��������һ�ɣ���ʼ˯����\n");
	    write("��һ�������ͽ��������硣\n");
	    me->set_temp("block_msg/all",1);
	    message_vision("$Nһ�������ڴ��ϣ���һ����������������������硣\n",me);
	} else
	{
	    write("�������½���һ�ɣ���ʼ˯����\n");
	    write("��һ�������ͽ��������硣\n");
	    me->set_temp("block_msg/all",1);
	    message_vision("$N�����½�������һ�ɣ���һ�����������������������\n",me);
	}

	me->set("no_get", 1);
	me->set("no_get_from", 1);

	me->set_temp("sleeped",1);
	if (where->query("hotel"))
	    me->delete_temp("rent_paid");

	me->disable_player(" <˯����>");
	me->start_call_out(bind((: call_other, __FILE__, "wakeup", me :), me), 12 + random(10));

	return 1;
}

void wakeup(object me)
{
	if (! me || ! me->query_temp("sleeped"))
		return;

	if (living(me))
	{
		me->delete_temp("sleeped");
		return;
	}

	me->enable_player();
	me->set_temp("block_msg/all", 0);
	me->delete("no_get");
	me->delete("no_get_from");
	me->delete_temp("sleeped");

	if (time() - me->query("last_sleep") >= 120)
	{
		me->set("qi",    me->query("eff_qi"));
		me->set("jing",  me->query("eff_jing"));
		if(me->query("neili") < me->query("max_neili"))
			me->add("neili", me->query("max_neili") -	 me->query("neili"));
		message("vision", me->name() + "һ����������������"
				  "�ػ��һ�½�ǡ�\n",
			environment(me), ({ me }));
		write("��һ��������ֻ���������档�ûһ���ˡ�\n");
		me->set("last_sleep", time());
	} else
	{
		message("vision", me->name() + "���Ժ����������۾���"
				  "��ɢ���������������\n",
			environment(me), ({ me }));
		write("�����Ժ���������˫�ۣ�����������\n");
	}
	me->write_prompt();
}

int help(object me)
{
	write(@HELP
ָ���ʽ : sleep
 
����˼�壬���ָ��������˯���ġ�
HELP );
	return 1;
}
