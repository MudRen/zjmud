// d/yanziwu/npc/chuanfu.c

inherit KNOWER;

void create()
{
	set_name("����", ({ "chuanfu", "chuan fu" }));
	set("gender", "����" );
	set("age", 22 + random(5));
	set("long",
	  "����һ������Ĵ��������Ž����Ŀ��������Χ��\n");
	set("attitude", "friendly");
	setup();
}
