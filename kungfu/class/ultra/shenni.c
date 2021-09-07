// shenni �Ϻ�����

#include <ansi.h>

inherit NPC;
inherit F_MASTER;
inherit F_NOCLONE;

mixed ask_opinion();

#define ULTRA_OPINION   "��ʦ"
#define OPINION_TYPE    HIY "�ڼҹ���" NOR 
#define MY_OPINION      "force"

string  *my_opinions = ({ "force" });

// ��ͷ�ļ�����������Ƕ��
#include "ultra.h"

void create()
{
	set_name("�Ϻ�����", ({ "nanhai shenni", "shenni", "nanhai" }) );
	set("title", HIG "����ʦ" NOR);
	set("gender", "Ů��");
	set("age", 91);
	set("long", "����һλ�������ᣬ��������ʲô��ͬ��\n");
	set("attitude", "peaceful");
	set("class", "bonze");
	set("str", 30);
	set("int", 37);
	set("con", 39);
	set("dex", 33);

	set("max_qi", 9999);
	set("max_jing", 9999);
	set("neili", 9999);
	set("max_neili", 9999);
	set("jiali", 70);

	set("combat_exp", 50000000);

	set("inquiry", ([
		"��ָ��ͨ" : "�����ұ̺��񹦹���ָ������ı仯�������ҵ��������������ڸ�һ�ˡ�",
		"����"     : (: ask_opinion :),
		"��ѧ����" : "�ú�����Լ�����ѧ����(martial-cognize)����ʱ��ʲô�书����С���ƣ�",
	]));

	set_skill("strike", 500);
	set_skill("finger", 500);
	set_skill("parry", 500);
	set_skill("dodge", 500);
	set_skill("force", 500);
	set_skill("staff", 500);
	set_skill("bluesea-force", 500);
	set_skill("martial-cognize", 500);
	set_skill("literate", 220);

	map_skill("parry", "bluesea-force");
	map_skill("force", "bluesea-force");
	map_skill("dodge", "bluesea-force");
	map_skill("finger", "bluesea-force");
	map_skill("strike", "bluesea-force");
	map_skill("staff", "bluesea-force");

	prepare_skill("finger", "bluesea-force");
	prepare_skill("strike", "bluesea-force");

	set("opinion/ultra",  1);
	set("opinion/master", 1);

	set("rank_info/self", "����");

	set("chat_chance_combat", 120);
	set("chat_msg_combat", ({
		(: exert_function, "powerup" :),
		(: exert_function, "shield" :),
		(: exert_function, "recover" :),
		(: perform_action, "staff.zhan" :),
		(: perform_action, "staff.lu" :),
		(: perform_action, "staff.jue" :),
		(: perform_action, "staff.zhu" :),
		(: perform_action, "staff.nan" :),
		(: perform_action, "strike.xuan" :),
		(: perform_action, "strike.bo" :),
	}));

	setup();
	carry_object("/clone/cloth/cloth")->wear();
	carry_object("/clone/weapon/zhubang")->wield();

	set("startroom", "/d/xiakedao/zhuwu2");
	check_clone();
}

void init()
{
	object me;

	if (! interactive(me = this_player()))
		return;

	me->delete_temp("want_opinion");
	if (ultrap(me))
		message_vision("$Nü��΢΢һ����\n", this_object(), me);
}

mixed ask_opinion()
{
	object me;
	object ob;

	me = this_player();

	if (me->query("combat_exp") < 200000)
		return "�ߣ�������书Ҳ�����������ۣ�";

	if (me->query("opinion/" MY_OPINION) == ULTRA_OPINION)
		return "�����ˣ����ڹ��������Ϊ�Ѿ��Ƶ�������ʦ�ˣ�Ҫ�Ǻ�ƶ����ϼ���Ҳ����";

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

		message_vision("$N��Ϊ��ŭ�Ķ�$n������û������æ���𣿡�\n",this_object(), me);
		return 1;
	}

	switch(me->query_temp("want_opinion/shenni"))
	{
	case 0:
		command("say �ðɣ����ǹ�һ�У�����һ��������");
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

	me->add_temp("want_opinion/shenni", 1);
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
	if (me->query("max_neili") > 4000) lvl += 20;
	return lvl;
}

void do_congration(object me)
{
	command("chat �����������ǲ���");
}

int accept_hit(object me)
{
	command("heng");
	command("say �����" + RANK_D->query_rude(me) + "���������ҵ������ˣ�");
	kill_ob(me);
	return 1;
}

int accept_fight(object me)
{
	object weapon;

	if (me->query("opinion/" MY_OPINION) == ULTRA_OPINION)
	{
		message_vision("$N��$n�������ܺã���Ҳ������ʦ�����ˣ�"
			       "���ɣ����ǱȻ�һ�£���\n",
			       this_object(), me);
		return 1;
	}

	if (! me->query_temp("want_opinion/shenni"))
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

	message_combatd("$N�������������$n������ԣ�����ͬʱ����������"
		       "��һ���ֻ������ͷ������������������Ȼ$N����"
		       "һ�����ջع�����û��һ�����ͣ�������$n��Ϊ�Ȼ��\n",
		       this_object(), me);
	if (me->query("neili") < 3000)
	{
		message_vision("$Nҡҡͷ��$n�������ʲ����������㣬����"
			       "�Ժ��������㽫�����������������ɣ���\n",
			       this_object(), me);
		return notify_fail("�������ǻ�ȥ����һ�������ɣ�\n");
	}
	me->set("neili", 0);
	

	call_out("check_opinion", 2, me);
	set_temp("opinion", me);
	me->delete_temp("want_opinion");
	message_vision("\n$Nһ���ֵ��������ˣ��������롣��\n",
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
	if (me->query("character") != "�ĺ�����")
	{
		command("say ���������Բ����������²��˺��ģ�"
			"��û����Ȥ���㣡");
		return -1;
	}

	if (skill == "martial-cognize")
		return 1;

	if (! ultrap(me))
	{
		command("say ��ѧ�ҵı̺��񹦣��㻹�����ʸ�"
			"������˴���ʦ��˵�ɣ�");
		return -1;
	}

	if (me->query_skill(skill, 1) >= 180)
	{
		command("say ���ˣ��Ҿͽ��㵽����ɣ��书����"
			"Ҫ���Լ����о����ǣ�");
		return -1;
	}

	if (skill != "bluesea-force")
		return 1;

	if (me->query_temp("can_learn/shenni/bluesea-force"))
		return 1;

	me->set_temp("can_learn/dugu/bluesea-force", 1);
	command("nod");
	command("say �����ҽ����ҵľ�ѧ�̺��񹦣��ܲ���ѧ��"
		"�Ϳ�����컯�ˣ�");
	return 1;
}

void unconcious()
{
	message("vision", "\n"HIR + name() + "��ɫһ�䣬����һ����"
		"Ѫ������һ�������Ų�����"NOR"\n", environment());
	command("chat �գ��գ��գ�ƶ��ȥҲ��");
	destruct(this_object());
}

void die()
{
	message("vision", "\n"HIR + name() + "���һ����������һ����"
		"Ѫ������һ�����ʹ˲�����"NOR"\n", environment());
	command("chat ƶ��ȥҲ��");
	destruct(this_object());
}
