// huang ����

#include <ansi.h>

inherit NPC;
inherit F_MASTER;
inherit F_NOCLONE;

mixed ask_opinion();

#define ULTRA_OPINION   "��ʦ"
#define OPINION_TYPE    HIY "��������" NOR 
#define MY_OPINION      "weapon"

string  *my_opinions = ({ "sword", "blade", "staff", "hammer",
			  "club", "whip",  "dagger", });

// ��ͷ�ļ�����������Ƕ��
#include "ultra.h"

void check_weapon();

void create()
{
	set_name("�������", ({ "dugu qiubai", "dugu" }) );
	set("title", HIC "����ʦ" NOR);
	set("gender", "����");
	set("age", 48);
	set("long", "���˳ϿҶغ�üĿ��Ƿ���������������\n");
	set("attitude", "peaceful");
	set("str", 38);
	set("int", 39);
	set("con", 32);
	set("dex", 33);

	set("max_qi", 9999);
	set("max_jing", 9999);
	set("neili", 9999);
	set("max_neili", 9999);
	set("jiali", 50);

	set("combat_exp", 50000000);

	set("inquiry", ([
		"���¾Ž�" : "�Ұ������书�ı仯����ھŽ�֮�У��㲻���ǽ����������������ƾ��޷�������а��",
		"����"     : (: ask_opinion :),
		"opinion"  : (: ask_opinion :),
		"��ѧ����" : "��ѧ����(martial-cognize)���������壬��ν����һͨͨ��ͨ��",
	]));

	set_skill("unarmed", 500);
	set_skill("sword", 500);
	set_skill("blade", 500);
	set_skill("staff", 500);
	set_skill("hammer", 500);
	set_skill("club", 500);
	set_skill("whip", 500);
	set_skill("dagger", 500);
	set_skill("throwing", 500);
	set_skill("parry", 500);
	set_skill("dodge", 500);
	set_skill("force", 500);
	set_skill("never-defeated", 500);
	set_skill("martial-cognize", 500);

	map_skill("sword", "never-defeated");
	map_skill("blade", "never-defeated");
	map_skill("staff", "never-defeated");
	map_skill("hammer", "never-defeated");
	map_skill("club", "never-defeated");
	map_skill("whip", "never-defeated");
	map_skill("dagger", "never-defeated");
	map_skill("parry", "never-defeated");
	map_skill("dodge", "never-defeated");
	map_skill("force", "never-defeated");

	set("opinion/ultra",  1);
	set("opinion/master", 1);

	set("chat_chance_combat", 120);
	set("chat_msg_combat", ({
		(: check_weapon :),
	}) );

	set("rank_info/self", "����");

	set("chat_chance_combat", 120);
	set("chat_msg_combat", ({
		(: exert_function, "powerup" :),
		(: exert_function, "shield" :),
		(: exert_function, "recover" :),
		(: perform_action, "sword.po" :),
		(: perform_action, "sword.tianhua" :),
		(: perform_action, "sword.wanli" :),
		(: perform_action, "sword.juemie" :),
	}));

	setup();
	carry_object("/clone/cloth/cloth")->wear();
	carry_object("/clone/weapon/zhujian")->wield();

	set("startroom", "/d/huashan/shandong");
	check_clone();
}

void init()
{
	object me;

	if (! interactive(me = this_player()))
		return;

	me->delete_temp("want_opinion");
	if (ultrap(me))
	{
		message_vision("$N΢΢һЦ����$n���˵�ͷ��\n",
			       this_object(), me);
	}
}

void check_weapon()
{
	if (objectp(query_temp("weapon")))
		return;

	message_vision("$N��̾һ����������$N��������������δ���"
		       "�֣��գ����ˣ���ȥҲ��\n", this_object());
	destruct(this_object());
}

mixed ask_opinion()
{
	object me;
	object ob;

	me = this_player();

	if (me->query("combat_exp") < 200000)
		return "�Ǻǣ�������书��̸ʲô���ۣ�";

	if (me->query("opinion/" MY_OPINION) == ULTRA_OPINION)
		return "������������������Ϊ�Ѿ��Ƶ�������ʦ�ˣ�����Ҫ��Ҫ�����У�";

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

		message_vision("$N���ڳ�˼��û�лش�$n��ֻ�ǰ��˰��֡�\n",
			       this_object(), me);
		return 1;
	}

	switch(me->query_temp("want_opinion/dugu"))
	{
	case 0:
		command("look " + me->query("id"));
		command("say �ðɣ����ñ�������һ�У��ҿ������ˮƽ��Ρ�");
		break;
	case 1:
		command("say ����˵������һ���ҿ�����");
		break;
	case 2:
		message_vision(CYN "$N" CYN "��ü��$n" CYN
			       "�������ҿ��������ǹ����µġ���"NOR"\n",
			       this_object(), me);
		break;
	case 3:
		command("say ���ұ�������죡");
		return 1;
	}

	me->add_temp("want_opinion/dugu", 1);
	return 1;
}

int calc_level(object me, string skill)
{
	int lvl;
	string sp;
	mapping action;

	lvl = me->query_skill(skill, 1) / 2;
	sp = me->query_skill_mapped(skill);
	if (! sp) return lvl;

	lvl += me->query_skill(sp, 1);
	action = SKILL_D(sp)->query_action(me, me->query_temp("weapon")); 
	if (mapp(action))
		lvl += (action["force"] + action["parry"] + action["dodge"] - 250) / 10;
	return lvl;
}

void do_congration(object me)
{
	command("chat ��λ" + RANK_D->query_respect(me) + "��Ҫ�������أ���֪ǿ�и���ǿ���֡�");
}

int accept_hit(object me)
{
	if (me->query_temp("want_hit/dugu") >= 2)
	{
		command("heng");
		command("say �²���������Ҫ�����Ǿ�ȥ���ɣ�");
		kill_ob(me);
		return 1;
	}

	command("shake");
	command("say ��λ" + RANK_D->query_respect(me) + "��"
		"����֮���м�óȻ���ơ�");
	me->add_temp("want_hit/dugu", 1);
	return 0;
}

int accept_fight(object me)
{
	object weapon;

	if (me->query("opinion/" MY_OPINION) == ULTRA_OPINION)
	{
		message_vision("$N��ϲ����$n�������ܺã������һ�û��"
			       "����ʦ���ֹ����У����ɣ���\n",
			       this_object(), me);
		return 1;
	}

	if (! me->query_temp("want_opinion/dugu"))
	{
		command("say ƽ���޹ʶ�ʲô�֣�");
		return 0;
	}

	if (! objectp(weapon = me->query_temp("weapon")))
	{
		command("say û�����㶯ʲô�֣�");
		return 0;
	}

	if (me->query("qi") * 100 / me->query("max_qi") < 80||
	    me->query("jing") * 100 / me->query("max_jing") < 80)
	{
		command("say ������״̬���ѣ�����Ϣ������˵�ɣ�");
		return 0;
	}

	command("nod");
	COMBAT_D->do_attack(me, this_object(), weapon);
	COMBAT_D->do_attack(this_object(), me, query_temp("weapon"));

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
	message_vision("\n$N���ͷ���������ˣ����ȵȻ�����������롣��\n",
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
	if (me->query("character") != "������")
	{
		command("say �ҿ�����Ը񲻹�������������"
			"����ѧϰ�书���������˰ɣ�");
		return -1;
	}

	if (skill == "martial-cognize")
		return 1;

	if (! ultrap(me))
	{
		command("say ��ѧ�ҵĲ����񹦣��㻹�����ʸ�"
			"������˴���ʦ��˵�ɣ�");
		return -1;
	}

	if (me->query_skill(skill, 1) >= 180)
	{
		command("say ���ˣ��Ҿͽ��㵽����ɣ��书����"
			"Ҫ���Լ����о����ǣ�");
		return -1;
	}

	if (skill != "never-defeated")
		return 1;

	if (me->query_temp("can_learn/dugu/never-defeated"))
		return 1;

	me->set_temp("can_learn/dugu/never-defeated", 1);
	command("nod");
	command("say �ҿ��Խ����Ҷ�����������Ĳ����񹦣�����"
		"���ܲ���ѧ����Ҫ����Ļ�Ե�ˣ�");
	return 1;
}

void unconcious()
{
	message("vision", "\n"HIR + name() + "��ɫһ�䣬����һ����"
		"Ѫ������һ�������Ų�����"NOR"\n", environment());
	command("chat �գ��գ��գ�����ȥҲ��");
	destruct(this_object());
}

void die()
{
	message("vision", "\n"HIR + name() + "���һ����������һ����"
		"Ѫ������һ�����ʹ˲�����"NOR"\n", environment());
	command("chat ����ȥҲ��");
	destruct(this_object());
}
