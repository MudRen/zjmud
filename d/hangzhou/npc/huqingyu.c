// huqingyu.c
#include <ansi.h>
#include <command.h>
inherit NPC;

void create()
{
	set_name("������",({ "hu qingyu","hu" }));
	set("gender", "����" );
	set("age", 63);
	set("long",
"�������ǵ���һ����ҽ�����ı��������ޱȡ������������֮����\n");
	set("combat_exp", 200000);
	set("attitude", "friendly");
	setup();
}
void init()
{
	object ob,me;
}
