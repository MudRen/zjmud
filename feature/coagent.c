// coagent.c

#include <ansi.h>
#include <dbase.h>

static int helping = 0;

int is_coagent() { return 1; }

int is_helping() { return helping; }

int start_help(object env, object helper, object ob)
{
	object me;

	command("yun powerup");
	me = this_object();
	if (! living(me)) return 0;

	if (env == environment())
	{
		if (this_object()->is_killing(ob->query("id")))
			return 1;

		message_vision(HIW + "$N��Ц��ֹ�����ø�" +
			       RANK_D->query_rude(ob) + "����Ҳ�����ң���\n",
			       me);
	} else
	{
		if (helping || me->is_fighting())
			return 0;

		message_vision(HIC + me->name() + "΢΢һ㶣��ƺ�������ʲô��"
			       "˫��һ�㣬���˳�ȥ��"NOR"\n", me);
    
		me->move(env);
		if (objectp(helper))
		{
			message_vision(random(2) ? HIW + "$N����Ӧ������$n�����ؾ��ţ���$N���ˣ���"NOR"\n" :
						   HIW + "$Nһ����������������������$N�أ����У���\n",
				       me, helper);
		}
	}

	me->kill_ob(ob);
	helping = 1;
	return 1;
}

void finish_help()
{
	string startroom;
	object me;

	me = this_object();
	if (! helping)
		return;

	startroom = me->query("startroom");
	if (! stringp(startroom) || startroom == "")
		return;

	if (base_name(environment()) != startroom)
	{
		message_vision("$N���˿����ܣ��Ҵҵ��뿪�ˡ�\n", me);
		me->move(startroom);
		message_vision("$N�Ҵҵظ��˹����������ĳ������·�ʲô"
			       "��û�з����Ƶġ�\n", me);
	}

	helping = 0;
}
