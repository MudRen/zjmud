// /d/xiakedao/shiroom14.c ���͵� ʯ��14

inherit ROOM;

void create()
{
	set("short", "ʯ��");
	set("long", @LONG
�������������ˮ��ʱ����ͷ����ʯ���ϵ��£�������Щù����
ʯ���յ����������Ͽ̵���ͼ���֡��Ҳ�һλ����ؤ���ڶ��Ŷ���ʯ
��(wall)��ȭ��ȭ��ʮ�㡣
LONG );
	set("exits", ([
		"north" : __DIR__"shihole4",
	]));
	set("item_desc", ([
		"��ʯ�ڡ�" : "����ǽ���ּ�ȴ���ڲ�ͬ���������֡�������Ϊ�᡹�������С��ڴ�"
				"�ֵıȻ��м䣬�����ܵ�һ�ζ�Сע����ǳ��һ��ԶԶ��ȥ��ȴ����"
				"��ͼ����ʶ��һ��ע�ǣ���Ի��ɽ�������𣬾����Գͷ�������\n"
		ZJOBACTS2"��Ħ:study wall\n",
	]));

	set("no_fight", 1);
	setup();
}

#include "/d/xiakedao/shiroom.h"
