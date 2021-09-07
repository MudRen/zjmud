// zhaixing.c ժ����

inherit NPC;
inherit F_MASTER;

#include "xingxiu.h"

string ask_me();
string ask_book();

void create()
{
	set_name("ժ����", ({ "zhaixing zi", "zhaixing" }));
	set("nickname", "�����ɴ�ʦ��");
	set("long", 
		"�����Ƕ�����Ĵ���ӡ������ɴ�ʦ��ժ���ӡ�\n"
		"����ʮ���꣬�����������۹���͸��һ˿����֮����\n");
	set("gender", "����");
	set("age", 35);
	set("attitude", "peaceful");
	set("class", "fighter");
	set("str", 26);
	set("int", 28);
	set("con", 26);
	set("dex", 26);
	
	set("max_qi", 2400);
	set("max_jing", 1200);
	set("neili", 2800);
	set("max_neili", 2800);
	set("jiali", 35);
	set("combat_exp", 320000);
	set("shen_type", -1);

	set_skill("force", 140);
	set_skill("huagong-dafa", 140);
	set_skill("guixi-gong", 140);
	set_skill("throwing", 120);
	set_skill("feixing-shu", 120);
	set_skill("dodge", 120);
	set_skill("zhaixinggong", 120);
	set_skill("whip", 80);
	set_skill("chanhun-suo", 80);
	set_skill("strike", 80);
	set_skill("chousui-zhang", 80);
	set_skill("claw", 80);
	set_skill("sanyin-wugongzhao", 80);
	set_skill("parry", 130);
	set_skill("poison", 115);
	set_skill("medical", 80);
	set_skill("xingxiu-qishu", 80);

	set("no_teach", ([
		"huagong-dafa" : "������Ҫ�������Դ��ڡ�",
	]));

	map_skill("force", "huagong-dafa");
	map_skill("dodge", "zhaixinggong");
	map_skill("strike", "chousui-zhang");
	map_skill("claw", "sanyin-wugongzhao");
	map_skill("parry", "chousui-zhang");
	map_skill("throwing", "feixing-shu");
	map_skill("whip", "chanhun-suo");

	prepare_skill("strike", "chousui-zhang");
	prepare_skill("claw", "sanyin-wugongzhao");

	set("inquiry", ([
		"���ĵ�"    : (: ask_me :),
		"�ؼ�"      : (: ask_book :),
		"��ɽ����"  : (: ask_book :),
	]));
	set("dan_count", 1);
	set("book_count", 1);

	set("chat_chance_combat", 120);
	set("chat_msg_combat", ({
		(: perform_action, "claw.zhua" :),
		(: perform_action, "strike.biyan" :),
		(: perform_action, "strike.huolang" :),
		(: perform_action, "strike.huoqiu" :),
		(: perform_action, "strike.huoyan" :),
		(: exert_function, "powerup" :),
		(: exert_function, "recover" :),
	}) );

	set_temp("apply/attack", 150);
	set_temp("apply/defense", 150);
	set_temp("apply/damage", 150);
	set_temp("apply/unarmed_damage", 150);

	create_family("������", 2, "����");

	setup();
	carry_object("/clone/weapon/lianzi")->wield();
}

void attempt_apprentice(object ob)
{
	command("say �ðɣ��Ҿ��������ˡ�");
	welcome(ob);
	command("recruit " + ob->query("id"));
}

string ask_me()
{
	mapping fam; 
	object ob;
	
	if (!(fam = this_player()->query("family")) || fam["family_name"] != "������")
		return RANK_D->query_respect(this_player()) + 
		"�뱾��������������֪�˻��Ӻ�̸��";

	if (query("dan_count") < 1)
		return "�������ˣ�û�����ĵ��ˡ�";

	add("dan_count", -1);
	ob = new("/d/xingxiu/obj/lianxindan");
	ob->move(this_player());
	return "��Щ���ĵ������õ��˰ɡ�";
}

string ask_book()
{
	mapping fam; 
	object ob;
	
	if (!(fam = this_player()->query("family")) || fam["family_name"] != "������")
		return RANK_D->query_respect(this_player()) + 
		"�뱾��������������֪�˻��Ӻ�̸��";

	if (query("book_count") < 1)
		return "�������ˣ�����ûʲôʣ���ˡ�";

	add("book_count", -1);
	ob = new("/clone/book/throw_book");
	ob->move(this_player());
	return "�ðɣ��Ȿ�����û�ȥ�úÿ����ɡ�";
}


