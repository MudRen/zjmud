//room: 
inherit ROOM;

void create()
{
  set("short","����");
  set("long",@LONG
����һ�����ŵ�С�ᣬһ���ű���ŵ�һ��Ũ���Ļ��㡣��
�й���һ����Ů���ͼ��ͼ�л��������װ��Ů����Ŀ���⣬��
�����ס����ﻹ��һ�Ų輸���������ӣ������������廨���棬
������һ�ȶ�����ͨ�������
LONG );

  set("exits",([
      "west" : __DIR__"huoting", 
  ]));  set("valid_startroom", 1);
  setup();
}

