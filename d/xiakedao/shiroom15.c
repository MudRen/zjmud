// /d/xiakedao/shiroom15.c ���͵� ʯ��15

inherit ROOM;

void create()
{
	set("short", "ʯ��");
	set("long", @LONG
�������Ũ�أ����������˲��پƴ����«����������˵���Ѿ�
�������壬أ�������ﲻͣ���ƣ����ĵ�ģ��ʯ��(wall)�ϵ�ͼ����
�����������һ��Ů���ڱǶ�����������֮ɫ��
LONG );
	set("exits", ([
		"west"  : __DIR__"shihole4",
	]));
	set("item_desc", ([
		"��ʯ�ڡ�" : "ǽ�����Ϸ����š��ۻ������᡹�������֡�����̵���³��������ɽ"
				"�ŵĹ��£����е��ֺ��д������࣬Ω��ΩФ�������ֻ���������Ҷ��"
				"�����衣\n"
		ZJOBACTS2"��Ħ:study wall\n",
	]));

	set("no_fight", 1);
	setup();
}

#include "/d/xiakedao/shiroom.h"
