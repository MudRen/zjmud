// Room: /d/city/shuyuan.c

inherit ROOM;

void create()
{
	set("short", "��Ժ");
	set("long", @LONG
��������Ժ�Ľ��ã�����������һ����Ⱦ��һλׯ���������������̫ʦ
���Ͻ�ѧ���Ǿ��ǵ�������������ˡ�������������������ѧ��ѧ����һ�Ź�
�ⰻȻ���鰸������������ǰ�棬���ϰ��ż��������˵���װ�鼮����������
�����һ�����(shujia)�����ڶ��������ʯ�̣������Ժ��ʷ���ƾá�ֵ��
һ�����Ƕ�ڽ���ǰ��ڵ�ѧ��(xuegui)��
LONG );
	set("item_desc", ([ /* sizeof() == 1 */
		"��ѧ�桿": "

  �ս����������տ���Ŀ��ҳ��
  ͨ��ʱ�������ζ�����ʫ����
  ���������ʣ���ΰ�ʱ���ꡣ
  ҹ���Խ���������Ҫ������

  ��ѧ���ѧ��������ʮ����\n"
ZJOBACTS2+ZJMENUF(3,3,9,28)"��ѧ:give 20 silver to zhu xi\n",
	]));

	set("no_fight", 1);
	set("no_sleep_room", 1);

	set("exits", ([ /* sizeof() == 2 */
		"up"    : __DIR__"shuyuan2",
		"south" : __DIR__"dongdajie1",
		"north" : __DIR__"shengxiantang",
	]));

	set("objects", ([ /* sizeof() == 1 */
		__DIR__"npc/zhu" : 1,
	]));

	setup();
}
