// /d/xiakedao/shishi11.c ���͵� ʯ��11

inherit ROOM;

void create()
{
	set("short", "ʯ��");
	set("long", @LONG
���ű�������г������أ���������������������ɽ��֮�ʡ���
��Ҳ�ǻ���������Ĭ�������ظ�����ϰ�书,���ȴ��֪Ϊ�����˼�
֧��ʯ��(wall)��Ͷ���˴�Ƭ��Ӱ��
LONG );
	set("exits", ([
		"west"  : __DIR__"shihole3",
	]));
	set("item_desc", ([
		"��ʯ�ڡ�" : "ǽ�����Ϸ����š�������캥���������֡��ֵ��·��̵����������"
				"���캥�Ĺ��¡���˵���캥ɱ��Ϊ��������֮��̻�سֵ��������⺷"
				"֮ɫ��κ�����޼���һ��վ������ɫ������\n"
		ZJOBACTS2"��Ħ:study wall\n",
	]));

	set("no_fight", 1);
	setup();
}

#include "/d/xiakedao/shiroom.h"
