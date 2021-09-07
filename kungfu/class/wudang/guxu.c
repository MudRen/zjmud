// guxu.c ����

#include <ansi.h>
#include "wudang.h"

inherit NPC;
inherit F_MASTER;

string ask_me();

void create()
{
	set_name("�������", ({ "guxu daozhang", "guxu" }));
	set("long", 
		"�����������۵ĵ��ӹ��������\n"
		"��������ʮ�꣬�����䵱�ɵ����¡�\n");
	set("gender", "����");
	set("age", 40);
	set("attitude", "peaceful");
	set("shen_type", 1);
	set("str", 22);
	set("int", 25);
	set("con", 26);
	set("dex", 23);
	
	set("max_qi", 2800);
	set("max_jing", 1400);
	set("neili", 3300);
	set("max_neili", 3300);
	set("jiali", 50);

	set("combat_exp", 500000);
	set("score", 28000);

	set_skill("force", 120);
	set_skill("wudang-xinfa", 120);
	set_skill("dodge", 100);
	set_skill("tiyunzong", 100);
	set_skill("strike", 110);
	set_skill("wudang-zhang", 110);
	set_skill("parry", 120);
	set_skill("sword", 100);
	set_skill("wudang-jian", 100);
	set_skill("taoism", 70);
  	set_skill("literate", 80);

	map_skill("force", "wudang-xinfa");
	map_skill("dodge", "tiyunzong");
	map_skill("unarmed", "taiji-quan");
	map_skill("parry", "wudang-jian");
	map_skill("sword", "wudang-jian");
	map_skill("strike", "wudang-zhang");

	prepare_skill("strike", "wudang-zhang");

	create_family("�䵱��", 3, "����");
	set("class", "taoist");

	set("inquiry", ([
			"���¾�" : (: ask_me :),
	]));
				
	set("book_count", 1);

	setup();
	carry_object("/clone/weapon/changjian")->wield();
	carry_object("/d/wudang/obj/greenrobe")->wear();
}

void attempt_apprentice(object ob)
{
	if (! permit_recruit(ob))
		return;

	if ((int)ob->query("shen") < 0)
	{
		command("say ���䵱���������������ɣ��Ե���Ҫ���ϡ�");
		command("say �ڵ��з��棬" + RANK_D->query_respect(ob) +
			"�Ƿ����ò�����");
		return;
	}
	command("say �ðɣ�ƶ�����������ˡ������䵱�������������ƣ�");
	command("recruit " + ob->query("id"));
}

string ask_me()
{
	object me;
	mapping fam; 
	object ob;

	me = this_player();

	if (!(fam = me->query("family")) 
	    || fam["family_name"] != "�䵱��")
	{
		return RANK_D->query_respect(me) + 
		"�뱾��������������֪�˻��Ӻ�̸��";
	}

	if (query("book_count") < 1)
		return "�������ˣ����ɵĵ����澭���ڴ˴���";

	add("book_count", -1);
	ob = new("/clone/book/daodejing-i");
	ob->move(me);
	return "�ðɣ��Ȿ�����¾������û�ȥ�ú����С�";
}

void reset()
{
	set("book_count", 1);
}
