inherit NPC;
#include <ansi.h>
inherit F_MASTER;
void create()
{
	set_name("��Ԫ��", ({ "qi yuankai", "qi" }));
	set("long", "��������ݳ���ȴ�������Ѱ�, �ƺ���������ҵ��\n");
	set("gender", "����");
	set("title", "������������ͷ��" );
	set("attitude", "friendly");
	set("age", 47);
	set("shen_type", -1);
	set("str", 20);
	set("int", 20);
	set("con", 20);
	set("dex", 20);
	set("max_qi", 900);
	set("max_jing", 500);
	set("neili", 800);
	set("max_neili", 800);
	set("jiali", 50);
	set("combat_exp", 80000);
	set("score", 100);

	set_skill("force", 100);
	set_skill("dodge", 100);
	set_skill("unarmed", 100);
	set_skill("parry", 100);

	setup();
	carry_object("/d/beijing/npc/obj/cloth6")->wear();
}
