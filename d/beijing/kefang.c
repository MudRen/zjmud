inherit ROOM;

void create()
{
	set("short", "���ͷ�");
	set("long", @LONG
һ���ţ�ֻ�����������ֳֽ䵶��Χ��һ����Ů��ƴ����ɱ��ֻ�Ǹ�����
Ů��������Ʒ��ס�ˣ��۲��������ǰ���Ů��ͷ����ð��˿˿��������Ȼ
�Ѿ���ȫ������ֻһ���۰���֧����ȥ�������ԵֵС����ϰ߰ߵ�㶼��Ѫ
����
LONG );
	set("exits", ([
		"west" : __DIR__"kediandayuan",
	]));
	set("objects", ([
		__DIR__"npc/dubi" : 1,
		__DIR__"npc/lama" : 6,
	]));
	setup();
}

