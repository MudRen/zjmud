//      xiaoyuan.c СԺ
inherit ROOM;

void create()
{
	set("short", "СԺ");
	set("long", @LONG
���������ڵ�СԺ����ʰ���൱�ɾ���������������
����ͺ����һ���ڰ�ʾ��ѩɽ�����֮ʢ��һ��Ҳ��
���ڱ�ʾ����Ŀڸ�Ҳ�治������Ϊ���߾��Ǹ�������
LONG );
	set("outdoors", "xueshan");
	set("exits", ([
		"west" : __DIR__"guangchang",
		"north" : __DIR__"chufang",
	]));
	setup();
}

