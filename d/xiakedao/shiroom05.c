// /d/xiakedao/shiroom05.c ���͵� ʯ��5

inherit ROOM;

void create()
{
	set("short", "ʯ��");
	set("long", @LONG
һλ�ɷ���ǵ���������һλ�ߴ���������д��书�����˾���
��ֿս�����ʽ������������󾢷罫���ڵû�Ѽ���������������
ʯ��(wall)��ͼ�����ǰವ½�롣
LONG );
	set("exits", ([
		"south" : __DIR__"shihole2",
	]));
	set("item_desc", ([
		"��ʯ�ڡ�" : "ǽ�����Ϸ����š�ʮ��ɱһ�ˡ��������֡����µ�ͼ��ȴ��һ������"
				"ɽˮ��������ɽ�����֣�����ľ��֦�����̲�һ��ǰ���ݺᣬ��Ҳ��"
				"���۽�������������ͼ��������Сע��\n"
		ZJOBACTS2"��Ħ:study wall\n",
	]));

	set("no_fight", 1);
	setup();
}

#include "/d/xiakedao/shiroom.h"
