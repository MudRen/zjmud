// daobaifeng.c ���׷�

#include <ansi.h>
#include "duan.h"

inherit NPC;
inherit F_MASTER;

void create()
{
	set_name("���׷�", ({ "dao baifeng", "dao" }));
	set("title",  "���������" );
	set("nickname",  CYN"����ɢ��"NOR );
	set("gender", "Ů��");
	set("long", @LONG
���Ǹ���ò������������ã��Ǹ�������Ů�ӣ�����Ӻ�����ʡ�������
������ʵ۶�����������ԭ����ˡ������ɷ�������մ���ǲݣ�һ
ŭ֮���ܵ�������˼ҡ�
LONG );
	set("age", 35);
	set("class", "royal");
	set("attitude", "friendly");
	set("shen_type", 1);
	set("str", 25);
	set("int", 25);
	set("con", 25);
	set("dex", 25);
	
	set("max_qi", 1800);
	set("max_jing", 900);
	set("neili", 2200);
	set("max_neili", 2200);
	set("jiali", 50);
	set("combat_exp", 420000);
	set("score", 8000);

	set_skill("force", 100);
	set_skill("dodge", 100);
	set_skill("parry", 100);
	set_skill("sword", 100);
	set_skill("cuff", 100);
	set_skill("strike", 100);
	set_skill("whip", 100);
	set_skill("kurong-changong", 100);
	set_skill("duanjia-sword", 100);
	set_skill("tiannan-step", 100);
	set_skill("jinyu-quan", 100);
	set_skill("wuluo-zhang", 100);
	set_skill("feifeng-whip", 100);
	set_skill("literate", 60);

	map_skill("force", "kurong-changong");
	map_skill("dodge", "tiannan-step");
	map_skill("whip", "feifeng-whip");
	map_skill("cuff", "jinyu-quan");
	map_skill("strike", "wuluo-zhang");
	map_skill("parry", "feifeng-whip");
	map_skill("sword", "duanjia-sword");
	prepare_skill("cuff", "jinyu-quan");
	prepare_skill("strike", "wuluo-zhang");

	setup();
	carry_object("/d/dali/npc/obj/cynrobe")->wear();
	carry_object("/d/dali/obj/fuchen")->wield();
	add_money("silver", 10);

	create_family("���ϻ���", 15, "����");
}

void attempt_apprentice(object ob)
{
	if (! permit_recruit(ob))
		return;

	if ((string)ob->query("gender") != "Ů��")
	{
		command("say ��ֻ��Ů���ӡ�");
		return;
	}

	command("say �ã����������ˡ�");
	command("recruit " + ob->query("id"));
	return;
}
