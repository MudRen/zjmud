// /kungfu/class/xueshan/daerba.c  �����
// by secret

inherit NPC;
inherit F_MASTER;

#include <ansi.h>

void create()
{
	set_name("�����", ({ "daerba huofo", "huofo" }));
	set("long",@LONG
���ǽ��ַ������µĴ���ӡ���÷������洫��
��һ����ɫ���ģ�ͷ��ɮñ��
LONG
	);
	set("title", HIY "���" NOR);
	set("gender", "����");
	set("age", 45);
	set("attitude", "heroism");
	set("shen_type", -1);
	set("str", 26);
	set("int", 19);
	set("con", 22);
	set("dex", 21);
	set("max_qi", 3200);
	set("max_jing", 1600);
	set("neili", 3400);
	set("max_neili", 3400);
	set("jiali", 50);
	set("combat_exp", 270000);

	set_skill("lamaism", 80);
	set_skill("literate", 80);
	set_skill("force", 150);
	set_skill("mizong-neigong", 150);
	set_skill("dodge", 100);
	set_skill("shenkong-xing", 100);
	set_skill("cuff", 140);
	set_skill("yujiamu-quan", 140);
	set_skill("parry", 140);
	set_skill("staff", 120);
	set_skill("xiangmo-chu", 120);

	map_skill("force", "mizong-neigong");
	map_skill("dodge", "shenkong-xing");
	map_skill("cuff", "yujiamu-quan");
	map_skill("parry", "mingwang-jian");
	map_skill("staff", "xiangmo-chu");

	prepare_skill("cuff", "yujiamu-quan");

	create_family("ѩɽ��", 3, "���");
	set("class", "bonze");

	setup();
	carry_object("/clone/weapon/gangzhang")->wield();
	carry_object("/d/xueshan/obj/y-jiasha")->wear();
	carry_object("/d/xueshan/obj/sengmao")->wear();
}

void attempt_apprentice(object ob)
{
	command("say �Ҳ���ͽ�ġ�");
}

