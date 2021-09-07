// wangchuyi.c ����һ
// By Lgg,1998.10

#include <ansi.h>
#include "quanzhen.h"

inherit NPC;
inherit F_MASTER;
inherit F_COAGENT;

string ask_me();

void create()
{
	set_name("����һ", ({"wang chuyi", "wang"}));
	set("gender", "����");
	set("age", 35);
	set("class", "taoist");
	set("nickname",RED"������"NOR);
	set("long",
		"������ȫ������֮������һ�����ˡ�������޳����������࣬\n"
		"��縺���Ʈ����ǰ����̬������\n");
	set("attitude", "peaceful");
	set("shen_type",1);
	set("str", 32);
	set("int", 30);
	set("con", 32);
	set("dex", 30);

	set("title","ȫ������֮��");
	set("chat_chance_combat", 60);
	set("chat_msg_combat", ({
		(: exert_function, "recover" :),
		(: exert_function, "recover" :),
		(: perform_action, "strike.ju" :),
		(: perform_action, "strike.ju" :),
		(: perform_action, "strike.ju" :),
		(: perform_action, "sword.ding" :),
		(: perform_action, "sword.ding" :),
		(: perform_action, "sword.ding" :),
	}));

	set("qi", 4200);
	set("max_qi", 4200);
	set("jing", 2100);
	set("max_jing", 2100);
	set("neili", 4500);
	set("max_neili", 4500);
	set("jiali", 100);

	set("combat_exp", 1200000);

	set_skill("force", 170);
	set_skill("quanzhen-xinfa", 170);
	set_skill("sword", 160);
	set_skill("quanzhen-jian",160);
	set_skill("dodge", 150);
	set_skill("jinyan-gong", 150);
	set_skill("parry", 170);
	set_skill("strike", 170);
	set_skill("chongyang-shenzhang", 170);
	set_skill("haotian-zhang", 170);
	set_skill("literate",100);
	set_skill("finger",150);
	set_skill("zhongnan-zhi", 170);
	set_skill("taoism",100);
	set_skill("medical", 180);
	set_skill("liandan-shu", 180);

	map_skill("force", "quanzhen-xinfa");
	map_skill("sword", "quanzhen-jian");
	map_skill("dodge", "jinyan-gong");
	map_skill("parry", "quanzhen-jian");
	map_skill("finger", "zhongnan-zhi");
	map_skill("strike", "haotian-zhang");
	prepare_skill("finger", "zhongnan-zhi");
	prepare_skill("strike", "haotian-zhang");

	create_family("ȫ���", 2, "����");

	set("book_count",1);
	set("inquiry", ([
		"ȫ���" :  "��ȫ��������µ����������ڡ�\n",
		"�ϵ�" : (: ask_me :),
		"�λ�ү" : (: ask_me :),
	]) );

	setup();

	carry_object("/clone/weapon/changjian")->wield();
	carry_object("/d/quanzhen/npc/obj/grayrobe")->wear();

}

void attempt_apprentice(object ob)
{
	if (! permit_recruit(ob))
		return;

	if ((int)ob->query_skill("quanzhen-xinfa", 1) < 90)
	{
		command("say ��ı����ڹ��ķ�����㣬�������Ը�������书��");
		return;
	}
	if ((int)ob->query("shen") < 8000)
	{
		command("say �ҿ��㻹�Ƕ���һЩ����֮�°ɡ�\n");
		return;
	}
	command("say �ðɣ��Ҿ����������ͽ���ˡ�");
	command("recruit " + ob->query("id"));
}

void destroying(object me, object obj)
{
	destruct(obj);
	return;
}

string ask_me()
{
	object me=this_player();

	if (me->query_temp("tmark/ָ") == 1)
	{
		me->add_temp("tmark/ָ",1);
		return("ȥ��ʦ��ȥ���λ�ү�����˵�λ�ү������������һ��ָ����
���ڸ���ʦ���ˡ�\n");
	} else
	{
		me->set_temp("tmark/ָ",0);
		return("�λ�ү������һ���������£����ڳ������˺����ˣ�����");
	}
}
