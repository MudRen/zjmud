// /d/xiakedao/shiroom07.c ���͵� ʯ��7

inherit ROOM;

void create()
{
	set("short", "ʯ��");
	set("long", @LONG
��������������ϰ�书������Ů�Ӷ��Ե������ĵã���ɫ���ص�
������ʯ��(wall)��ϰ�������Աߵ�������������ȴ�����Ի��ƺ�
δ���ž���
LONG );
	set("exits", ([
		"west" : __DIR__"shihole2",
	]));
	set("item_desc", ([
		"��ʯ�ڡ�" : "ǽ�����Ϸ����š����˷���ȥ���������֡��ֵ��·��̵������е�һ"
				"��Ů�ӣ��������磬�������������Ҳ���������ơ�����ע�ƣ�С��"
				"���ƣ����޼���ס����һ��ע�����ߣ�����֮����\n"
		ZJOBACTS2"��Ħ:study wall\n",
	]));

	set("no_fight", 1);
	setup();
}

#include "/d/xiakedao/shiroom.h"
