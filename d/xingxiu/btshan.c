// room: /d/xingxiu/btshan
// Jay 3/27/96

inherit ROOM;

void create()
{
	set("short", "����ɽ");
	set("long", @LONG
���Ǵ�˵�����صİ���ɽ��ԶԶ��ȥ��������ɳ�ѻ��γɵ�ɽ�����
һֻ���յļ�����һ��ɽ�����������ǰ��ɽ�ź�һ��С·ͨ��һ��ɽ��
�ϵ�ɽׯ�������ǡ�������ŷ�������լ��һ���˴���ȥ�������ˡ�
LONG
	);
	set("exits", ([ 
	    "east" : __DIR__"shamo4",
	    "westup" : __DIR__"btshan1",
	]));

	setup();
}
