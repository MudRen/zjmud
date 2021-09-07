inherit NPC;
inherit F_MASTER;

#include "xingxiu.h"

#define SWMUDING	"/clone/misc/swmuding"

string ask_me();

void create()
{
	set_name("����", ({ "a zi", "a", "zi"}));
	set("nickname", "������Сʦ��");
	set("long", 
		"�����Ƕ�������Ӱ��ϡ�\n"
		"������������������������͸��һ��а����\n");
	set("gender", "Ů��");
	set("age", 15);
	set("attitude", "peaceful");
	set("class", "fighter");
	set("shen_type", -1);
	set("str", 18);
	set("int", 28);
	set("con", 20);
	set("dex", 24);
	
	set("max_qi", 300);
	set("max_jing", 300);
	set("neili", 500);
	set("max_neili", 500);
	set("jiali", 10);
	set("combat_exp", 45000);

	set_skill("force", 60);
	set_skill("guixi-gong", 60);
	set_skill("huagong-dafa", 20);
	set_skill("dodge", 40);
	set_skill("zhaixinggong", 40);
	set_skill("strike", 40);
	set_skill("chousui-zhang", 40);
	set_skill("claw", 40);
	set_skill("sanyin-wugongzhao", 40);
	set_skill("whip", 80);
	set_skill("chanhun-suo", 80);
	set_skill("parry", 40);
	set_skill("poison", 50);
	set_skill("staff", 10);
	set_skill("tianshan-zhang", 10);

	set("no_teach", ([
		"huagong-dafa" : "�����������ɽ���ɣ��ҿɲ�Ը��������",
	]));

	map_skill("force", "guixi-gong");
	map_skill("dodge", "zhaixinggong");
	map_skill("strike", "chousui-zhang");
	map_skill("claw", "sanyin-wugongzhao");
	map_skill("parry", "tianshan-zhang");
	map_skill("staff", "tianshan-zhang");
	map_skill("whip", "chanhun-suo");

	prepare_skill("strike", "chousui-zhang");
	prepare_skill("claw", "sanyin-wugongzhao");

	create_family("������", 2, "����");

	set("chat_chance_combat", 20);
	set("chat_msg_combat", ({
		(: perform_action, "whip.suo" :),
		(: exert_function, "recover" :),
	}) );

	set("swmuding", 1);
	set("inquiry", ([
		"ľ��" : "�ֿ�����һ��ѣ����Լ�ȥ�Ұɣ�",
		"��ľ����" : "����ʦ���õģ������Ҹ�ɶ��",
	]));

	setup();

	carry_object("/clone/weapon/rousisuo")->wield();
	carry_object("/d/xingxiu/obj/xxqingxin-san");
	carry_object("/d/xingxiu/obj/xxqingxin-san");
}

void attempt_apprentice(object ob)
{
	command("say �ðɣ��Ҿ��������ˡ�");
	welcome(ob);
	command("recruit " + ob->query("id"));
}

int accept_kill(object who)
{
	object ob;

	if (! living(this_object()))
		return 1;

	if (! query("swmuding"))
	{
		command("say ����ľ��ԭ����ȷ����������Ǻ���������������");
		command("inn " + who->query("id"));
		tell_object(who, "�㿴������һ���������������ӣ�������ͷһ��\n");
		return -1;
	}

	if (who->query("family/family_name") !=
	    query("family/family_name"))
		return 1;

	ob = find_object(SWMUDING);
	if (objectp(ob) && environment(ob))
	{
		command("say ���أ�����ľ����ı�����������");
		tell_object(who, "�㿴�������鲻������α�����ɵ�̾��һ������\n");
		return -1;
	}

	if (who->query("combat_exp") >= 500000 &&
	    who->query("shen") < -10000)
	{
		message_vision("$N��У����֣����֣��Ҹ���ľ�����ǣ�\n",
			       this_object());
		SWMUDING->move(this_object());
		command("give " + SWMUDING->query("id") +
			" to " + who->query("id"));
		set("swmuding", 0);
		return -1;
	}

	command("say ��˵��û��ľ���ˣ�����ô���ţ�");
	return 1;
}
