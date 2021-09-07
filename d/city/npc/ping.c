
#include <ansi.h>
#include <medical.h>
inherit NPC;
inherit F_DEALER;

string ask_job();
int do_peiyao(string arg);
int working(object me);
int halt_working(object me);

void create()
{
	set_name("ƽһָ", ({ "ping yizhi" }));
	set("title", "ҩ���ϰ�");
	set("gender", "����");
	set("long", "������ҽ���߳��ġ�ɱ����ҽ��ƽһָ���������Ը�Ź֣�����ʲô�˶�ҽ�ġ�\n");
	set("age", 65);
	set("int", 38);
	set("qi", 1000);
	set("max_qi", 1000);
	set("jing", 1000);
	set("max_jing", 1000);
	set("shen_type", 1);
	set("combat_exp", 500000);
	set("attitude", "heroism");
	set("inquiry", ([
		"����"   : (: ask_job :),
	]));
	setup();
	carry_object("/clone/misc/cloth")->wear();
}

void init()
{
	add_action("do_peiyao", "peiyao");
}

string ask_job()
{
	object me;
	object *obs;

	me = this_player();
	if (me->query_temp("job/peiyao"))
		return "����ɵĻ��������ô��";

	if (me->query("combat_exp") > 500000)
		return "�������Ҳ̫�������˰ɡ�";

	if (me->query("combat_exp") < 150)
		return "����㾭�飬��һ���嶼û�У��ҿ�����ҩ�ʶ��˲�������";

	if (me->query("qi") < 5)
		return "�㻹����ЪЪ�ɣ���һ�۳��������ҿɸ�������";

	if (! interactive(me))
		return "...";

	obs = filter_array(all_inventory(environment()),
			   (: interactive($1) &&
			      $1 != $(me) &&
			      $1->query_temp("job/peiyao") &&
			      query_ip_number($1) == query_ip_number($(me)) :));
	//if (sizeof(obs) > 50)
	//	return "�����Ѿ���" + obs[0]->name() + "�ڸɻ��ˣ���ȵȰɡ�";

	me->set_temp("job/peiyao", 1);
//	if(me->query("zjvip/level")&&me->query_temp("tuoguan/ping"))
		tell_object(me,ZJFORCECMD("peiyao"));
	tell_object(me,ZJEXIT"northwest:"RED"�ж�"NOR":halt\n");
	return "�ã���Ͱ���"ZJURL("cmds:peiyao")ZJSIZE(15)"��ҩ"NOR"(peiyao)�ɣ��������⼸ζ��";
}

int do_peiyao(string arg)
{
	object me;

	me = this_player();
	if (me->is_busy())
		return notify_fail("����æ���أ����ż���\n");

	if (! me->query_temp("job/peiyao"))
	{
		message_vision("$N����ץ��ζҩ���ƣ�������$nŭ�ȵ������ҷ��£����Ҷ���\n",me, this_object());
		return 1;
	}
	me->set_temp("job/step", 1);
	me->start_busy(bind((: call_other, __FILE__, "working" :), me),bind((: call_other, __FILE__, "halt_working" :), me));
	tell_object(me, "�㿪ʼ������\n");
	return 1;
}

int working(object me)
{
	object ob;
	string msg;
	int finish;
	int b;

	if (! me->query_temp("job/step"))
		me->set_temp("job/step", 1);

	if (! living(me))
	{
		me->delete_temp("job/peiyao");
		me->delete_temp("job/step");
		return 0;
	}

	finish = 0;
	me->receive_damage("qi", 1);
	switch (me->query_temp("job/step"))
	{
	case 1:
		msg = "$N��������ѡ����һЩҩ�ġ�";
		break;
	case 2:
		msg = "$N��ҩ�ķŽ�ҩ�ʣ�ʹ������������";
		break;
	case 3:
		msg = "$N��ҩ�ķ��˷�������ʹ������������";
		break;
	case 4:
		msg = "$N��ҩ�ķ��˷�������ʹ������������";
		break;
	case 5:
		msg = "ҩ�Ľ���������м������һ��";
		break;
	case 6:
		msg = "��м��$N�ĵ�Ū��Խ��Խϸ���𽥱���˷�ĩ��";
		break;
	default:
		msg = "$N��ҩ�İ��ã��ݸ�$n��";
		finish = 1;
		break;
	}
	msg += "\n";

	if (finish)
	{
		msg += "$n����$N���ҩ����ͷ���������������Ǹ���ı��꣡\n";
		me->delete_temp("job/peiyao");
		me->delete_temp("job/step");

		b = 10 + random(11);
		me->add("combat_exp", b);
		me->improve_potential(b/2);

		ob = new("/clone/money/coin");
		ob->set_amount(b/3);
		ob->move(me, 1);
	}
	msg = replace_string(msg, "$N", "��");
	msg = replace_string(msg, "$n", name());
	tell_object(me, msg);

	if (finish)
	{
		if (b > 0)
		{
			tell_object(me, HIC "\n������" + chinese_number(b/3) + "��ͭ�塢" + chinese_number(b) + "�㾭���" + chinese_number(b/2) + "��Ǳ�ܡ�"NOR"\n");
		}
		if (random(1000) == 1)
		{
			msg = "$n��$N�ٺ�һЦ�������ɵò������е���˼���������ĥ���������͸��������ɡ�\n";
			message_vision(msg, me, this_object());
			ob = new("/clone/misc/dymo");
			ob->move(me, 1);
			tell_object(me, HIM "\n������һ��" + ob->name() + HIM "��"NOR"\n");
		}
//		if(me->query("zjvip/level")&&me->query_temp("tuoguan/ping"))
		if(!interactive(me)) return 0;
			tell_object(me,ZJFORCECMD("ask "+this_object()->query("id")+" about ����"));
		return 0;
	}
	me->add_temp("job/step", 1);
	return 1;
}
int halt_working(object me)
{
	message_vision("$N�����еĻ�һ˦�����µ��������ˣ������ˣ�\n", me);
	me->delete_temp("job/peiyao");
	me->delete_temp("job/step");
	return 1;
}
