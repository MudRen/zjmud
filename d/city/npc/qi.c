// qi.c �ݳ���

#include <ansi.h>
#include <command.h>

inherit NPC;
inherit F_DEALER;

int do_answer();

void create()
{
	set_name("�ݳ���", ({ "qi changfa", "qi" }));
	set("title", "��ʬ���Ŵ���");
	set("nickname", HIR "���˲��õ���" HIC "Ը" HIR "���Ϲ�" NOR);

	set("gender", "����");
	set("age", 48);
       set("skill_qi", 1);	
       set("str", 100);
	set("long",
		"���ϰ�����Ǳ�����ƣ���ν�����겻���ţ����Ź����ꡣ\n");
	set_skill("unarmed", 50);
	set_skill("dodge", 50);
	set_skill("higgling", 300);

	set_temp("apply/damage", 15);

	set("combat_exp", 800000);
	set("attitude", "friendly");
/*
	set("inquiry", ([
		"����������" : "��������������ƽ�һ����",
		"�����"     : "���ΰٶ������������ܻ",
		"�쾦���"   : "��Ȼ������������������������������ܽ�ٶ���",
		"�ּۻ���"   : "����ѧ(higgling)... �Һ����",
	]));
*/
	set("vendor_goods", ([
//		"/clone/vip/avipcard" : 2000000,
//		"/clone/vip/yanzhi" : 2000000,
//		"/clone/vip/xuantie" : 3000000,
//		"/clone/vip/hantie"  : 3000000,
//		"/clone/vip/wujins"  : 3000000,
//		"/clone/vip/butian"  : 8000000,
//		"/clone/vip/tiancs"  : 8000000,
		"/clone/medicine/baoming" : 3000000,
		"/clone/medicine/jiuhua"  : 3000000,
		"/d/shenlong/obj/hua4"    : 5000000,
		"/clone/misc/zhujingchan" : 15000000,
//		"/clone/vip/shenliwan"   : 100000000,
//		"/clone/vip/xisuidan"    : 100000000,
//		"/clone/vip/xiandan"     : 100000000,
//		"/clone/vip/unknowdan"   : 100000000,
//		"/clone/vip/jinpiao"  : 8000000,
//		"/clone/vip/lingzhi"  : 5000000,
	]));

	setup();
	set_max_encumbrance(100000000);
	if (clonep()) keep_heart_beat();
}

void init()
{
	add_action("do_buy", "buy");
	add_action("do_list", "list");
	add_action("do_drop", "drop");
}

void heart_beat()
{
	string start_room;
	object ob;

	if (stringp(start_room = query("startroom")) &&
	    find_object(start_room) == environment())
	{
		foreach (ob in all_inventory(environment()))
		{
			if (! ob->is_character() ||
			    interactive(ob) || playerp(ob) || ob->is_chatter() ||
			    ob->query_temp("owner") ||
			    ob->query_leader())
				continue;

			if (stringp(start_room = ob->query("startroom")) &&
			    find_object(start_room) == environment())
				continue;

			message_vision("$N������ü����$n���˳�ȥ��\n",
				       this_object(), ob);
			ob->move("/d/city/beidajie1");
		}
	}

	::heart_beat();
}

int do_drop(string arg)
{
	int i;
	object *obs;
	object ob;
	object me;

	if (! arg)
		return 0;

	me = this_player();
	if (objectp(ob = present(arg, me)) &&
	    ob->is_character() && ! playerp(ob))
	{
		me->add_temp("static/drop_npc", 1);
		if (me->query_temp("static/drop_npc") > 1 &&
		    me->query("combat_exp") >= 50000)
		{
			message_vision("$N��ŭ�������������" +
				       RANK_D->query_rude(ob) +
				       "���������ң���\n˵��ֻ��$N"
				       "����һ�ţ���$n��" + ob->name() +
				       "һ���߳����⡣\n", this_object(), me);
			ob->move("/d/city/beidajie1");
			me->move("/d/city/beidajie1");
			message("vision", "ֻ�������۹�һ����" + me->name() +
					  "����һ�����˳�����\n",
				environment(me), me);
			me->receive_damage("qi", 1);
			me->die();
			return 1;
		}

		message_vision("$Nŭ�������������ٸ������ң�Ӱ���ҵ����⡣��\n"
			       "˵��ֻ��$N����һ�ţ���$n��" + ob->name() +
			       "һ���߳����⡣\n", this_object(), me);
		ob->move("/d/city/beidajie1");
		me->move("/d/city/beidajie1");
		message("vision", "ֻ�������۹�һ����" + me->name() +
				  "����һ�����˳�����\n",
			environment(me), me);
		me->receive_damage("qi", 1);
		me->unconcious();
		return 1;
	}

	if (! DROP_CMD->main(me, arg))
		return 0;

	if (! command("get " + arg))
		return 1;

	obs = all_inventory(this_object());
	for (i = 0; i < sizeof(obs); i++)
		if (! obs[i]->is_character()) destruct(obs[i]);
	if (! random(5))
	{
		switch (random(4))
		{
		case 0:
			command("say �ջ����ۣ�С��֮·��");
			break;
		case 1:
			command("kok " + this_player()->query("id"));
			command("say �������������������Ԫ��");
			break;
		case 2:
			command("say �ܼ��ӣ��ܼ��ӣ�");
			break;
		default:
			command("heihei");
			break;
		}
	}
	return 1;
}

int accept_object(object who, object ob)
{
	if (ob->query("money_id"))
	{
		if (! who->query_temp("mark/��"))
			who->set_temp("mark/��", 0);
	
		if (ob->query("money_id") && ob->value() >= 10000)
		{
			message_vision("$Nͬ��ָ��$nһЩ�ּۻ��۵õļ��ɡ�\n",
				       this_object(), who);
			who->add_temp("mark/��", ob->value() / 100);
			destruct(ob);
			return 1;
		}
		command("say �����Ǯ... ����Ȼ��ɻ��濴���ϣ�");
		return -1;
	}

	switch (random(6))
	{
	case 0:
		command("say �ã��ã�");
		break;
	case 1:
		command("say ��Ҫ�͸��ң�");
		break;
	}

	if (! ob->is_character())
	{
		destruct(ob);
		return -1;
	}

	return 1;
}

void recover()
{
	mapping p;

	clear_condition(0);
	p = query_entire_dbase();
	p["eff_qi"] = p["max_qi"];
	p["qi" ] = p["max_qi"];
	p["eff_jing"] = p["max_jing"];
	p["jing" ] = p["max_jing"];
}

void unconcious()
{
	message_vision("\n$N�ߺ�������������������... Ŷ����\n",
		       this_object());
	recover();
}

void die()
{
	message_vision("\n$N���һ����������ʹ����������æ�ͳ������������������š�\n",
		       this_object());
	recover();
}

int recognize_apprentice(object ob, string skill)
{
	if (ob->query_temp("mark/��") < 1)
		return 0;

	if (skill != "higgling")
		return 0;

	ob->add_temp("mark/��", -1);
	return 1;
}
