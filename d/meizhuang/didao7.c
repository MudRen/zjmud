// didao7.c
inherit ROOM;

void create()
{
	set("short", "÷ׯ�ܵ�");
	set("long", @LONG
����һ���谵��ʪ�ĵص����ص��ܳ������ߵ���������̫������
��ѣ��ص����Ե�ǽ���ϻ��źܶ಻֪�����Ժ���֮�ֵıڻ�������
�����൱�ѿ���������һ�����ţ������߽��˲ŷ���ԭ�������ڵģ�
��û��������
LONG
	);
	set("exits", ([ /* sizeof() == 4 */
	    "west" : __DIR__"didao6",
	    "north" : __DIR__"laofang",
	]));
	set("no_clean_up", 0);

	setup();
}
