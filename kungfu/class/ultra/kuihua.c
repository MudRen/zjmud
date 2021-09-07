// kuihua ����̫��

#include <ansi.h>

inherit NPC;
inherit F_MASTER;
inherit F_NOCLONE;

mixed ask_opinion();

#define ULTRA_OPINION   "��ʦ"
#define OPINION_TYPE    HIY "������" NOR 
#define MY_OPINION      "dodge"

string  *my_opinions = ({ "dodge" });

// ��ͷ�ļ�����������Ƕ��
#include "ultra.h"

void create()
{
	set_name("����̫��", ({ "kuihua taijian", "kuihua", "taijian" }) );
	set("title", HIR "����ʦ" NOR);
	set("gender", "����");
	set("age", 99);
	set("long", "���������������������𣬲�֪��ϲ��ŭ��\n");
	set("attitude", "peaceful");
	set("str", 31);
	set("int", 39);
	set("con", 34);
	set("dex", 36);

	set("max_qi", 9999);
	set("max_jing", 9999);
	set("neili", 9999);
	set("max_neili", 9999);
	set("jiali", 80);

	set("combat_exp", 50000000);

	set("inquiry", ([
		"��������" : "������д��һ�������Ṧ������ĵã���ô��������Ȥ��",
		"����"     : (: ask_opinion :),
		"opinion"  : (: ask_opinion :),
		"��ѧ����" : "ѧϰ����书��û��������ѧ����(martial-cognize)����Ҳ���ᣡ",
	]));

	set_skill("unarmed", 500);
	set_skill("finger", 500);
	set_skill("parry", 500);
	set_skill("dodge", 500);
	set_skill("force", 500);
	set_skill("sword", 500);
	set_skill("kuihua-mogong", 500);
	set_skill("martial-cognize", 500);
	set_skill("literate", 220);

	map_skill("parry", "kuihua-mogong");
	map_skill("force", "kuihua-mogong");
	map_skill("dodge", "kuihua-mogong");
	map_skill("unarmed", "kuihua-mogong");
	map_skill("finger", "kuihua-mogong");
	map_skill("sword", "kuihua-mogong");

	prepare_skill("finger", "kuihua-mogong");
	prepare_skill("unarmed", "kuihua-mogong");

	set("opinion/ultra",  1);
	set("opinion/master", 1);

	set("rank_info/self", "����");

	set("chat_chance_combat", 120);
	set("chat_msg_combat", ({
		(: exert_function, "powerup" :),
		(: exert_function, "shield" :),
		(: exert_function, "recover" :),
		(: perform_action, "finger.you" :),
		(: perform_action, "finger.wu" :),
		(: perform_action, "finger.gui" :),
	}));

	setup();
	carry_object("/clone/cloth/cloth")->wear();
	carry_object("/clone/misc/spin")->wield();

	set("startroom", "/d/beijing/shanlu3");
	check_clone();
}

void init()
{
	object me;

	if (! interactive(me = this_player()))
		return;

	me->delete_temp("want_opinion");
	if (ultrap(me))
		message_vision("$Nɨ��$nһ�ۡ�\n", this_object(), me);
}

mixed ask_opinion()
{
	object me;
	object ob;

	me = this_player();

	if (me->query("combat_exp") < 200000)
		return "�٣�������书ֻ��ץץ����";

	if (me->query("opinion/" MY_OPINION) == ULTRA_OPINION)
		return "�ţ����Ṧ�������Ϊ�Ѿ��Ƶ�������ʦ�ˣ�Ҫ������Ȥ���ǹ����У�";

	if (is_fighting(me))
		return "��������ʲô������Ӯ���ң����Լ����Լ����۰ɣ�";

	if (me->is_fighting())
		return "��Ȼ���ɣ����Ҹ������ǡ�";

	if (objectp(ob = query_temp("opinion")))
	{
		if (ob == me)
		{
			command("say ����ʲô������Ҫ���ҡ�");
			return 1;
		}

		message_vision("$N��Ϊ��ŭ�Ķ�$n������û������æ���𣿡�\n",
			       this_object(), me);
		return 1;
	}

	switch(me->query_temp("want_opinion/kuihua"))
	{
	case 0:
		command("say �ðɣ���׼�����˾ͽ���һ�У��ҿ������ˮƽ��Ρ�");
		break;
	case 1:
		command("say ��׼����û�У����˾����ɡ�");
		break;
	case 2:
		message_vision(CYN "$N" CYN "��ü��$n" CYN
			       "�������ҿ��������ǹ����µġ���"NOR"\n",
			       this_object(), me);
		break;
	case 3:
		command("say ����ұ���������죡");
		return 1;
	}

	me->add_temp("want_opinion/kuihua", 1);
	return 1;
}

int calc_level(object me, string skill)
{
	int lvl;
	string sp;

	lvl = me->query_skill(skill, 1) / 2;
	sp = me->query_skill_mapped(skill);
	if (! sp) return lvl;

	lvl += me->query_skill(sp, 1);
	lvl += 20;
	return lvl;
}

void do_congration(object me)
{
	command("chat* heihei " + me->query("id"));
}

int accept_hit(object me)
{
	command("heng");
	command("say ���ò��ͷ��ˣ�");
	kill_ob(me);
	return 1;
}

int accept_fight(object me)
{
	object weapon;

	if (me->query("opinion/" MY_OPINION) == ULTRA_OPINION)
	{
		message_vision("$N��$n�������ܺã���Ҳ���Ƕ�������ˣ�"
			       "���ɣ����ǱȻ�һ�£���\n",
			       this_object(), me);
		return 1;
	}

	if (! me->query_temp("want_opinion/kuihua"))
	{
		command("say ���ʲôҪ���Ҷ��֣�");
		return 0;
	}

	command("look " + me->query("id"));
	COMBAT_D->do_attack(this_object(), me, 0);

	if (me->query("qi") <= 0)
	{
		message_vision("\n$Nҡҡͷ��$n�����������ڵ��书"
			       "�����Զ������һ�ж��Ӳ�ס����\n",
			       this_object(), me);
		return notify_fail("����Ҫ�úõ����������ˡ�\n");
	}

	call_out("check_opinion", 2, me);
	set_temp("opinion", me);
	me->delete_temp("want_opinion");
	message_vision("\n$Nһ���ֵ������������������롣��\n",
		       this_object(), me);
	return notify_fail("���������ļ������õ�һ�����\n");
}

int accept_kill(object me)
{
	if (me->query("combat_exp") < 500000)
	{
		message_vision("$N��ŭ����������С����ʲô"
			       "�ң����ҹ�����˵��һ�ư�$n�����ڵء�\n",
			       this_object(), me);
		me->unconcious();
		return -1;
	}
	command("sigh");
	command("say �ܺã����껹��û������ʲô�Һ��ҽ����ĸ��֣�");
	return 1;
}

int recognize_apprentice(object me, string skill)
{
	if (me->query("character") != "���ռ�թ")
	{
		command("say ������û����������ľ���֮����"
			"�ǻ�ȥ�ɣ�");
		return -1;
	}

	if (skill == "martial-cognize")
		return 1;

	if (! ultrap(me))
	{
		command("say ��ѧ�ҵĿ����񹦣��㻹�����ʸ�"
			"������˴���ʦ��˵�ɣ�");
		return -1;
	}

	if (me->query_skill(skill, 1) >= 180)
	{
		command("say ���ˣ��Ҿͽ��㵽����ɣ��书����"
			"Ҫ���Լ����о����ǣ�");
		return -1;
	}

	if (skill != "kuihua-mogong")
		return 1;

	if (me->query_temp("can_learn/kuihua/kuihua-mogong"))
		return 1;

	me->set_temp("can_learn/kuihua/kuihua-mogong", 1);
	command("nod");
	command("say �����Ҿʹ�������񹦰ɣ���Ҫ��ʲô����"
		"���䣬��������ȥ���˵ģ�");
	return 1;
}

void unconcious()
{
	message("vision", "\n"HIR + name() + "��ɫһ�䣬����һ����"
		"Ѫ������һ�������Ų�����"NOR"\n", environment());
	command("chat �գ��գ��գ��Ϸ�ȥҲ��");
	destruct(this_object());
}

void die()
{
	message("vision", "\n"HIR + name() + "���һ����������һ����"
		"Ѫ������һ�����ʹ˲�����"NOR"\n", environment());
	command("chat �Ϸ�ȥҲ��");
	destruct(this_object());
}
