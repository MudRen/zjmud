// /NPC xuzhu.c

inherit NPC;
inherit F_MASTER;
inherit F_COAGENT;
inherit F_QUESTER;

#include <ansi.h>
#include "lingjiu.h"

void create()
{
	set_name("����", ({ "xu zhu", "xu", "zhu" }));
	set("long", @LONG
����һ����ʮ������������ˣ�Ũü���ۣ����ı��ӱ�ƽ����, ��ò
��Ϊ��ª����һ���������µĳ���, ��ʹ�����Լ��־���
LONG );
	set("title", "���չ�������");
	set("gender", "����");
	set("age", 26);
	set("nickname", HIM "����" NOR);
	set("shen_type",1);
	set("attitude", "peaceful");

	set("str", 26);
	set("int", 27);
	set("con", 42);
	set("dex", 27);

	set("qi", 5500);
	set("max_qi", 5500);
	set("jing", 2600);
	set("max_jing", 2600);
	set("neili", 7800);
	set("max_neili", 7800);
	set("jiali", 100);

	set("combat_exp", 2450000);
	set("score", 40000);
	set_skill("force", 270);
	set_skill("dodge", 240);
	set_skill("parry", 270);
	set_skill("hand",250);
	set_skill("strike", 250);
	set_skill("sword", 240);

	set_skill("zhemei-shou", 250);
	set_skill("liuyang-zhang", 250);
	set_skill("yueying-wubu", 240);
	set_skill("bahuang-gong", 270);
	set_skill("tianyu-qijian", 240);
	set_skill("lingjiu-xinfa", 120);

	map_skill("force", "bahuang-gong");
	map_skill("strike","liuyang-zhang");
	map_skill("dodge", "yueying-wubu");
	map_skill("hand", "zhemei-shou");
	map_skill("parry", "liuyang-zhang");
	map_skill("sword", "tianyu-qijian");

	prepare_skill("hand", "zhemei-shou");
	prepare_skill("strike", "liuyang-zhang");	

	create_family("���չ�",2, "����");

	set("chat_chance_combat", 120);
	set("chat_msg_combat", ({
		(: perform_action, "hand.jiubu" :),
		(: perform_action, "strike.jiutian" :),
		(: perform_action, "strike.zhong" :),
		(: exert_function, "recover" :),
		(: exert_function, "powerup" :),
	}));

	set_temp("apply/attack", 150);
	set_temp("apply/defense", 150);
	set_temp("apply/damage", 100);
	set_temp("apply/unarmed_damage", 100);
	set_temp("apply/armor", 200);

	setup();
	carry_object("/d/lingjiu/obj/changpao")->wear();
	add_money("silver", 50);
}

void attempt_apprentice(object ob)
{
	if (! permit_recruit(ob))
		return;

	if ((int)ob->query_skill("lingjiu-xinfa", 1) < 100) 
	{
		command("say " + RANK_D->query_respect(ob) +
			"�Ƿ�Ӧ�ö����������ķ���");
		return;
	}

	if ((int)ob->query("max_neili") < 800) 
	{
		command("say �����书ȫ������������������"
			"�������ɣ�����������������˵�ɣ�");
		return;
	}

	if ((int)ob->query("combat_exp") < 200000)
	{
		command("say ��ʵս���鲻�㣬���Ǻúö���һ����˵�ɡ�");
		return;
	}

	if ((string)ob->query("gender")=="Ů��")
	{
		message_vision("����Ŀ��˼Ƭ��, ˵�������ð�, ��"
			       "���������ˡ���\n", ob);
		command("recruit " + ob->query("id"));
		if((string)ob->query("class") != "dancer")
			ob->set("class", "dancer");
		return;
	} else
	{
		message_vision("��������㿴�˰���,˵����"
			       "�����²������������ҵ������?��\n", ob);
		return;
	}
}

void unconcious()
{
	die();
}
