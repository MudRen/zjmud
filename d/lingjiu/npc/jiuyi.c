// NPC jiuyi.c

#include <ansi.h>

inherit KNOWER;

void create()
{
	set_name("�������", ({ "jiuyi daoren", "jiuyi"}));
	set("long",
	    "��������һƷ����Ƹ�ĸ��֣���ĸ��ݣ����������������ġ�\n"+
	    "���Ṧ���ߣ���ʹ�׹�����ƾһ���׹������򣬳�Ϊ������һ�����֡�\n");
	set("title", "����һƷ�ø���");
	set("gender", "����");
	set("nickname", HIR "�׶��ھ���֮��" NOR);
	set("age", 40);
	set("shen_type", -1);
	set("attitude", "peaceful");

	set("str", 27);
	set("int", 23);
	set("con", 24);
	set("dex", 30);

	set("max_qi", 2000);
 	set("qi", 2000);
	set("jing", 1000);
	set("max_jing", 1000);
	set("neili", 3000);
	set("max_neili", 3000);
	set("jiali", 20);

	set("combat_exp", 1600000);
	set("score", 1500);
	setup();
}

