// chuanfu.c ����

#include <ansi.h>

inherit KNOWER;

void create()
{
	set_name("����", ({ "chuan fu" }));
	set("gender", "����");
	set("age", 56);
	set("long", @LONG
����һ������������Ŀ��ڰ��ߣ����������������ˡ�������͸¶
��һ�ɽ���֮����
LONG );

	set("combat_exp", 100000);

	set("eff_qi", 2000);
	set("qi", 2000);
	set("max_neili", 1000);
	set("neili", 2000);
	set("jiali", 50);

	set_skill("force", 100);
	set_skill("unarmed", 100);
	set_skill("dodge", 100);
	set_skill("parry", 100);
	set("inquiry", ([
		"����" : "�Ƕ������д�ô���������ҡ�",
	]));

	setup();
	carry_object("/clone/misc/cloth")->wear();
}

void unconcious()
{
	::die();
}
