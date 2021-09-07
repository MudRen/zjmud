// zhu.c ����

#include <ansi.h>

inherit NPC;
inherit F_DEALER;

string ask_buy();
string ask_job();
int  do_copy(string arg);
int do_answer();
int  working(object me);
int  halt_working(object me);

void create()
{
	set_name("����", ({ "zhu xi" }));
	set("long", "����������Ϊ������һ����ѧ�ң��������īˮ�Ⱥ���Ҫ�\n");
	set("gender", "����");
	set("age", 65);
	set("no_get", 1);
	set_skill("literate", 500);
	 set("teacher",1);
	set_skill("unarmed", 80);
	set_skill("dodge", 80);
	set_skill("parry", 80);
	set_temp("apply/attack", 80);
	set_temp("apply/defense", 80);
	set_temp("apply/damage", 20);

	set("combat_exp", 400000);
	set("shen_type", 1);
	set("inquiry", ([
	    "����" : (: do_answer :),
	    "����" : (: ask_job :),
	    "����" : "�裿�㲻���ҵ��������㣿�ߣ�",
	]));
	set("vendor_goods", ({
		"/clone/book/lbook1",
		"/clone/book/lbook2",
		"/clone/book/lbook3"
	}));
	setup();

	set("chat_chance", 1);
	set("chat_msg", ({
		"����˵��������֮�£�Ī������������֮����Ī��������\n",
		"����˵���������ˣ�С�������ɣ����������δ������֮��\n",
		"����˵������ѧ֮�����������¡���������ֹ�����ơ� \n",
		"����˵����������֪���������ģ�������ң��ι�ƽ���¡�\n",
	}) );
}

void init()
{
	add_action("do_copy", "copy");
	add_action("do_list", "list");
	add_action("do_buy", "buy");
}

int do_answer()
{
	::do_list();
	write(name() + HIR"�����������˵������������ǻ����ʵ��ͯ�����۰���"NOR"\n");
	return 1;
}

int recognize_apprentice(object ob)
{
	if (ob->query_temp("mark/��") < 1)
		return 0;

	ob->add_temp("mark/��", -1);
	return 1;
}

int accept_object(object who, object ob)
{
	if (! who->query_temp("mark/��"))
		who->set_temp("mark/��", 0);

	if (ob->query("money_id") && ob->value() >= 2000)
	{
		message_vision("����ͬ��ָ��$NһЩ����д�ֵ����⡣\n", who);
		who->add_temp("mark/��", ob->value() / 50);
		    destruct(ob);
		return 1;
	}

	command("say �����ѧ�棬���ѧ������Ҫ��ʮ��������");
	return 0;
}

void auto_copy(object me)
{
	if(!interactive(me)) return;
	if(!me->query_temp("pending/auto_copy"))
		return;
	if(me->is_busy())
		call_out("auto_copy",1,me);
	else if( (int)me->query("qi") < 50||(int)me->query("jing") < 50 )
	{
		tell_object(me,"�������㣬��Ϣ�С�����\n");
		call_out("auto_copy",10,me);
	}
	else
	{
		tell_object(me,"�й��У��������顣����������\n");
		tell_object(me,ZJFORCECMD("ask "+this_object()->query("id")+" about ����"));
	}
}

string ask_job()
{
	object me;
	object *obs;

	me = this_player();
	if (me->query_temp("job/copy"))
		return "���㳭�����㳭���ˣ�";

	if (me->query("combat_exp") < 1)
		return "��Ȼ������ֻ�ǳ����飬������ս��������ô�Ҫ����С��å��������ô�죿";

	if (me->query("combat_exp") > 500000)
		return "������Ҳ�����飿�����������ˣ����߰���";

	if (me->query("qi") < 20)
		return "�ҿ�����ɫ���а�����Ъ����ɣ��ҿɲ��볭�鳭����������";

	if (me->query("jing") < 10)
		return "�ҿ��㾫���а����ܳ�������ô��";

	if (me->query_int() < 25 && me->query_skill("literate", 1) < 1)
		return "��˵��������ô����Ҳ�����飿";

	if (! interactive(me))
		return "...";

	obs = filter_array(all_inventory(environment()),
			   (: interactive($1) && $1 != $(me) && $1->query_temp("job/copy") && query_ip_number($1) == query_ip_number($(me)) :));
	//if (sizeof(obs) > 0)
	//	return "�����Ѿ���" + obs[0]->name() + "�ڸɻ��ˣ���ȵȰɡ�";

	me->set_temp("job/copy", 1);
	tell_object(me,ZJFORCECMD("copy"));
	tell_object(me,ZJEXIT"northwest:"RED"�жϳ���"NOR":halt\n");
	return "�ã���Ͱ���"ZJURL("cmds:copy")ZJSIZE(15)"����"NOR"(copy)�ɣ���īֽ���������";
}

int do_copy(string arg)
{
	object me;

	me = this_player();
	if (me->is_busy())
		return notify_fail("����æ���أ����ż���\n");

	if (! me->query_temp("job/copy"))
	{
		message_vision("$N����ë�ʣ�����պī��������$n��ȵ������ҷ��£����Ҷ��ķ��ı���\n",me, this_object());
		return 1;
	}

	me->set_temp("job/step", 1);
	me->set_temp("pending/auto_copy", 1);
	me->start_busy(bind((: call_other, __FILE__, "working" :), me),
		       bind((: call_other, __FILE__, "halt_working" :), me));
	tell_object(me, "�㿪ʼ������\n");
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
		me->delete_temp("job/copy");
		me->delete_temp("job/step");
		return 0;
	}

	finish = 0;
	me->receive_damage("jing", 1);
	me->receive_damage("qi", 2);
	switch (me->query_temp("job/step"))
	{
	case 1:
		msg = "$N�ù���̨����������ī��";
		break;
	case 2:
		msg = "$N����īĥ�ò���ˣ�����ë�ʣ����������������";
		break;
	case 3:
		msg = "$N��պī֭���������飬̯��ֽ�ţ���ʼ��д��";
		break;
	case 4:
	case 6:
		msg = "$N�۾�����ĳ�д�鼮��";
		break;
	case 5:
		msg = "$Nպ��պī��������ϸ�س�д��";
	case 7:
		msg = "$N���Ϸ������鼮��ֽ��Խ��Խ��";
		break;
	default:
		msg = "$N���鼮���ã���ֽ��ī���ɣ�װ���ɲᣬ�ݸ�$n��";
		finish = 1;
		break;
	}
	msg += "\n";

	if (finish)
	{
		object ob;
		msg += "$n����$N��д���飬����������У����ӿɽ̣�"
		       "���Ǹ���ı��꣡�������������ѧ���Ļ���\n";
		me->delete_temp("job/copy");
		me->delete_temp("job/step");

		b = 10 + random(11);
		me->add_temp("mark/��", 20);
		me->add("combat_exp", b);
		me->improve_potential((b * 1) / 3);

		if (me->query_skill("literate", 1) < 100)
			me->improve_skill("literate", (b + 1) / 2);

		ob = new("/clone/money/coin");
		ob->set_amount(b/2);
		ob->move(me, 1);
	}

	msg = replace_string(msg, "$N", "��");
	msg = replace_string(msg, "$n", name());
	tell_object(me, msg);

	if (finish)
	{
		if (b > 0)
		{
			tell_object(me, HIC "\n������" + chinese_number(b/2) + "��ͭ�塢" + chinese_number(b) + "�㾭���" + chinese_number((b * 1) / 3) + "��Ǳ�ܡ�"NOR"\n");
		}
//		if(me->query("zjvip/level")&&me->query_temp("tuoguan/zhu"))
			call_out("auto_copy",1,me);
		return 0;
	}

	me->add_temp("job/step", 1);
	return 1;
}

int halt_working(object me)
{
	message_vision("$N�����еı�īֽ�ⶪ��һ�ԣ���ɧ����ʲôѽ�������Ͳ����˸ɵĻ\n", me);
	me->delete_temp("job/copy");
	me->delete_temp("pending/auto_copy");
	me->delete_temp("job/step");
	return 1;
}
