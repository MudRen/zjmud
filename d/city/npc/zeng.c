// zeng.c

#include <ansi.h>

inherit NPC;
inherit F_DEALER;

string ask_job();

int  working(object me);
int  halt_working(object me);

void create()
{
	set_name("����", ({ "zeng rou" }));
	set("gender", "Ů��");
	set("age", 16);
	set("per", 25);
	set("con", 25);
	set("int", 25);
	set("dex", 25);
	set("str", 25);
	set("long",
"����Τ��ү��֪���ڼ�����С檣������￪�������̣���Щ��֪��"
"�������·�������˵�Ƕ���Τ��ү�ӹ���Ū�����Ľ�Ʒ������ô˵��"
"�����������\n");
	set_skill("unarmed", 60);
	set_skill("changquan", 60);
	map_skill("unarmed", "changquan");
	set_temp("apply/damage", 15);

	set("combat_exp", 50000);
	set("attitude", "friendly");
	set("vendor_goods", ({
		__DIR__"cloth/belt",
		__DIR__"cloth/boots",
		__DIR__"cloth/bu-shoes",
		__DIR__"cloth/cloth",
		__DIR__"cloth/color-dress",
		__DIR__"cloth/fu-cloth",
		__DIR__"cloth/gui-dress",
		__DIR__"cloth/hat",
		__DIR__"cloth/jade-belt",
		__DIR__"cloth/liu-dress",
		__DIR__"cloth/marry-dress",
		__DIR__"cloth/mini-dress",
			}));
	
	set("inquiry", ([
	    "����" : (: ask_job :),
	]));

	setup();
	carry_object(__DIR__"cloth/feature")->wear();
}

void init()
{
	add_action("do_list", "list");
	add_action("do_buy", "buy");
	add_action("do_sew", "sew");
}

void auto_sew(object me)
{
	if(!interactive(me)) return;
	if(!me->query_temp("pending/auto_sew"))
		return;
	if(me->is_busy())
		call_out("auto_sew",1,me);
	else if( (int)me->query("qi") < 50||(int)me->query("jing") < 50 )
	{
		tell_object(me,"�������㣬��Ϣ�С�����\n");
		call_out("auto_sew",10,me);
	}
	else
	{
		tell_object(me,"�й��У��������ơ�����������\n");
		tell_object(me,ZJFORCECMD("ask "+this_object()->query("id")+" about ����"));
	}
}

string ask_job()
{
	object me;
	object *obs;

	me = this_player();
	if (me->query_temp("job/sew"))
		return "���������·���Ū����ô��";

	if (me->query("gender") != "Ů��")
		return "��Ů���ӼҵĻ���Ҳ���ɣ�";

	if (me->query("combat_exp") > 35000)
		return "�������ã������ǿ���ʲô�õ��Լ�ѡ���ɣ������ɻ�Ҳ̫ί���ˣ�";

	if (me->query("qi") < 30)
		return "����ɫ��ô�������Ъ����ɡ�";

	if (me->query("jing") < 30)
		return "�㾫��ͷ���а�������ҵ�������̤�ˣ�";

	if (me->query_int() < 20)
		return "����...����ô���ֱ��ŵģ�Ҳ�����·���";

	if (! interactive(me))
		return "...";

	obs = filter_array(all_inventory(environment()),
			   (: interactive($1) &&
			      $1 != $(me) &&
			      $1->query_temp("job/sew") &&
			      query_ip_number($1) == query_ip_number($(me)) :));
	if (sizeof(obs) > 0)
		return "�����Ѿ���" + obs[0]->name() + "�ڰ��������������ˡ�";

	me->set_temp("job/sew", 1);
	tell_object(me,ZJFORCECMD("sew"));
	tell_object(me,ZJEXIT"northwest:"RED"�жϷ���"NOR":halt\n");
	return "�ã���Ͱ�������"ZJURL("cmds:sew")ZJSIZE(15)"�÷�"NOR"(sew)��С��ɣ������������������";
}

int do_sew(string arg)
{
	object me;

	me = this_player();
	if (me->is_busy())
		return notify_fail("����æ���أ����ż���\n");

	if (! me->query_temp("job/sew"))
	{
		message_vision("$N͵͵������һ�����룬$nһ����߸����"
			       "����ҷ��£���ʲô����ģ�\n",
			       me, this_object());
		return 1;
	}

	me->set_temp("job/step", 1);
	me->set_temp("pending/auto_sew", 1);
	me->start_busy(bind((: call_other, __FILE__, "working" :), me),
		       bind((: call_other, __FILE__, "halt_working" :), me));
	tell_object(me, "�㿪ʼ���ҡ�\n");
	return 1;
}

int working(object me)
{
	string msg;
	int finish;
	int b;

	if (! me->query_temp("job/step"))
		me->set_temp("job/step", 1);

	if (! living(me))
	{
		me->delete_temp("job/sew");
		me->delete_temp("job/step");
		return 0;
	}

	finish = 0;
	me->receive_damage("jing", 1);
	me->receive_damage("qi", 2);
	switch (me->query_temp("job/step"))
	{
	case 1:
		msg = "$N����һ�����룬�������ߡ�";
		break;
	case 2:
		msg = "$Nչ�����ϣ��������ӱȻ��˰��졣";
		break;
	case 3:
		msg = "$N��������������ӣ����¼�����ӡ��";
		break;
	case 4:
	case 6:
		msg = "$Nר����־��һ��һ�ߵķ��ҡ�";
		break;
	case 5:
		msg = "$N��ü���˿����ӣ�������˼��";
	case 7:
		msg = "$N�ᶯ����ϸָ���������´����·���ģ�������ĳ����ˡ�";
		break;
	default:
		msg = "$N���·���ã�������ϣ����õݸ�$n��";
		finish = 1;
		break;
	}
	msg += "\n";

	if (finish)
	{
		object ob;
		msg += "$n����$N��������·�����ͷ���������е���˼��\n";
		me->delete_temp("job/sew");
		me->delete_temp("job/step");

		b = 8 + random(8);
		me->add("combat_exp", b);
		me->improve_potential((b + 2) / 3);

		ob = new("/clone/money/coin");
		ob->set_amount(60);
		ob->move(me, 1);
	}

	msg = replace_string(msg, "$N", "��");
	msg = replace_string(msg, "$n", name());
	tell_object(me, msg);

	if (finish)
	{
		if (b > 0)
		{
			tell_object(me, HIC "\n������" +
				    chinese_number(b) +
				    "�㾭���" +
				    chinese_number((b + 2) / 3) +
				    "��Ǳ�ܡ�"NOR"\n");
		}
		call_out("auto_sew",1,me);
		return 0;
	}

	me->add_temp("job/step", 1);
	return 1;
}

int halt_working(object me)
{
	message_vision("$N�����е�����һ�ӣ��ֹ�����"
		       "û���������ﲻ���ˣ�\n", me);
	me->delete_temp("job/sew");
	me->delete_temp("pending/auto_sew");
	me->delete_temp("job/step");
	return 1;
}

