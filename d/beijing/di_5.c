#include <room.h>
inherit ROOM;

void create()
{
	set("short", "�������");
	set("long", @LONG
�����Ǳ����ǵذ��ŵ����֡��ֵ�����������������֣������������ﲻ
����������ƥ�������С���������й�����ˣ��Ͼ��Ͽ��Ŀ����������ŵ���
�������Լ�������ˣ�ŵ���ͯ������һ����æ���ֵ�ʢ�����󡣱����Ǿ�����
����Ǯׯ���ϱ��ǵذ��ŵ����ֹ㳡��
LONG );
       set("exits", ([
		"north" : __DIR__"qianzhuang",
		"south" : __DIR__"di_xigc",
		"east" : __DIR__"di_dajie1",
		"west" : __DIR__"di_4",
	]));

	set("outdoors", "beijing");
	setup();
}

