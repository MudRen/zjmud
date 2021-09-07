// laopu.c ɨ������

#include "roomnpc.h"

inherit NPC;
inherit F_GUARDER;

void do_wield();
void do_unwield();
int  accept_object(object who, object ob);

void create()
{
	set_name("ɨ������", ({"lao pu", "saodi laopu"}) );
	set("gender", "����" );
	set("age", 50 + random(20));
	set("long", "����һ��ɨ�ص������ˣ���������ȥ�ƺ���������\n");
	set("attitude", "friendly");

	set("max_qi", 4000);
	set("max_jing", 2000);
	set("max_neili", 4200);
	set("neili", 4200);
	set("jiali", 70);

	set_skill("force", 200);
	set_skill("parry", 200);
	set_skill("dodge", 200);
	set_skill("sword", 200);
	set_skill("cuff",  200);
	set_skill("strike",200);
	set_skill("huashan-xinfa", 200);
	set_skill("feiyan-huixiang", 200);
	set_skill("huashan-sword", 200);
	set_skill("hunyuan-zhang", 200);
	set_skill("poyu-quan", 200);

	map_skill("force", "huashan-xinfa");
	map_skill("parry", "huashan-sword");
	map_skill("sword", "huashan-sword");
	map_skill("dodge", "feiyan-huixiang");
	map_skill("cuff" , "poyu-quan");
	map_skill("strike", "hunyuan-zhang");

	prepare_skill("cuff", "poyu-quan");
	prepare_skill("strike", "hunyuan-zhang");

	set("chat_chance", 30);
	set("chat_msg", ({
		(: do_unwield :),
	}));

	set("chat_chance_combat", 80);
	set("chat_msg_combat", ({
		(: do_wield :),
	}));

	setup();

	carry_object("/clone/weapon/gangjian");
	carry_object("/clone/cloth/cloth")->wear();
}

void init()
{
	::init();
	add_action("do_invite", "invite");
	add_action("do_show", "show");
}

void do_unwield()
{
	command("unwield jian");
}

void do_wield()
{
	command("wield jian");
}

int accept_object(object who, object ob)
{
	object obn;

	if (! ob->query("money_id"))
		return 0;

	if (is_owner(who))
	{
		message_vision(name() + "��$Nʩ��һ��\n", who);
		destruct(ob);
		return 1;
	}
	return 0;
}

int accept_hit(object ob)
{
	if (is_owner(ob))
	{
		message_vision("$N��ü�����Ķ�$n�������ɲ�Ҫ���ҿ���"
			       "����Ц����\n", this_object(), ob);
		return 0;
	}

	return ::accept_hit(ob);
}

int accept_fight(object ob)
{
	if (is_owner(ob))
	{
		message_vision("$N����һ������æ��$n������С�Ĳ��ң�С"
			       "�Ĳ��ң���\n", this_object(), ob);
		return 0;
	}

	return ::accept_fight(ob);
}

int accept_kill(object ob)
{
	if (is_owner(ob))
	{
		message_vision("$Nһ����̾����������Ȼ���˲������ˣ���"
			       "�հգ���������������ȥ�������ˡ���\n"
			       "˵�գ����˶���ɨ�ѣ�ƮȻ��ȥ��\n",
			       this_object(), ob);
		destruct(this_object());
		return 0;
	}

	return ::accept_kill(ob);
}
