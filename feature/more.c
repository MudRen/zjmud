// more.c

#include <ansi.h>
#include <dbase.h>

#define LINES_PER_PAGE	  35

void zj_more(string tab,string topic,string *text, int line, int page)
{
	int i, j, now, all;
	string show;

	show = tab;
	if(page<1) page = 1;
	all = sizeof(text)/line;
	if(page>(all+1)) page = all+1;
	
	i = page*line;
	if (i >= sizeof(text)) i = sizeof(text) - 1;
	j = (page-1)*line+1;
	if( j<0 ) j = 0;
	now = i/line;
	if(i%line) now += 1;
	if(now<1) now = 1;
	if(sizeof(text)%line) all += 1;
	if(all>1)
		show += sprintf("========= "HIY"%d/%dҳ"NOR" ========="ZJBR NOR,now,all);
	show += implode(text[j..i], ZJBR);
	if(all>1)
		show += "\n"ZJOBACTS2+ZJMENUF(2,2,9,30)"��һҳ:help "+topic+" "+(page-1)+ZJSEP"��һҳ:help "+topic+" "+(page+1);
	write(show+"\n");
}

void more(string cmd, string *text, int line)
{
	int i, j;
	string show;

	show = ZJMORETXT;

	switch (cmd)
	{
	default:
		i = line + LINES_PER_PAGE;
		if (i >= sizeof(text)) i = sizeof(text) - 1;
		show += implode(text[line..i], ZJBR);
		if (i == sizeof(text) - 1)
		{
			write(show+"\n");
			return;
		}
		line = i + 1;
		break;

	case "b":
		line -= LINES_PER_PAGE * 2;
		if (line <= 0)
		{
			line = 0;
			show += WHT "-------- �ļ��Ķ��� --------"NOR ZJBR;
		}

		i = line + LINES_PER_PAGE;
		if (i >= sizeof(text)) i = sizeof(text) - 1;
		show += implode(text[line..i], ZJBR);
		line = i + 1;
		break;

	case "q":
		write("\n");
		return;
	}
//	show += sprintf(ZJBR NOR WHT "== δ����� " HIY "%d%%" NOR WHT " == (ENTER ������һҳ��q �뿪��b ǰһҳ)" NOR,line * 100 / sizeof(text));
	show += sprintf(ZJBR WHT "======== δ����� " HIY "%d/%dҳ" NOR WHT " ========== " NOR,line / LINES_PER_PAGE,sizeof(text)/LINES_PER_PAGE+1);
	write(show+"\n");
	input_to("more", text, line);
}

void s_write(string msg)
{
	message("vision", msg, this_object());
}

void start_more(string msg)
{
	int len;

	if (! stringp(msg) || (len = strlen(msg)) < 1)
		// û������
		return;

	if (query("env/no_more"))
	{
		s_write(msg);
		if (msg[len - 1] != '\n') write("\n");
		return;
	}

	write("\n");
	more("", explode(msg, "\n"), 0);
}

void more_file(string cmd, string file, int line, int total)
{
	int i;
	string show;
	string content;
	string *text;
	int goto_line;
	int page;
	int not_show;

	show = "";

	page = LINES_PER_PAGE;
	goto_line = line;

	if (! cmd) cmd = "";
	if (sscanf(cmd, "%d,%d", goto_line, page) == 2)
	{
		if (page < goto_line)
		{
			i = goto_line;
			goto_line = page;
			page = i;
		}
		page = page - goto_line + 1;
	} else
	if (sscanf(cmd, "n%d", page))
		;
	else
	if (sscanf(cmd, "%d", goto_line))
		; else
	{
		switch (cmd)
		{
		default:
			cmd = "";
			break;

		case "b":
			goto_line = line - LINES_PER_PAGE * 2;
			if (goto_line > 1)
				break;
			// else continue to run selection "t"
		case "t":
			goto_line = 1;
			break;

		case "q":
			write(show);
			return;
		}
	}

	if (page > 301)
	{
		show += "������ʾ����������С�ڵ���300��\n";
		not_show = 1;
	} else
	{
		not_show = 0;

		if (! goto_line) goto_line = 1;
		if (! page) page = 1;

		if (goto_line < 0)
		{
			// The goto line < 0, mean look bottom
			goto_line += total;
			if (goto_line  < 1)
				goto_line = 1;
		}

		if (page < 0)
		{
			// The page size < 0, mean look previous page
			goto_line += page;
			if (goto_line < 1)
			{
				page -= goto_line - 1;
				goto_line = 1;
			}
			page = -page;
		}
	}

	line = goto_line;

	if (! not_show)
	{
		if (line == 1)
			show += WHT "-------- �ļ��Ķ��� --------"NOR"\n";
		else
		if (cmd != "")
			show += sprintf(HIW "-------- �ӵ� %d �п�ʼ %d �� --------"NOR"\n",
					goto_line, page);
	
		content = read_file(file, line, page);
		if (! content)
		{
			i = 0;
		} else
		{
			text = explode(replace_string(content, "\n", " \n") + " ", "\n");
			if (page > sizeof(text))
				page = sizeof(text);
			for (i = 0; i < page; i++)
				text[i] = sprintf(NOR "%-8d%s", i + line, text[i]);
			content = implode(text[0..i - 1], "\n") + "\n";
		
			show += content;
		}
	}

	if (not_show || i > 1)
	{
		show += NOR WHT "- δ��(" HIY + total +
			NOR WHT ") - (�س�������"
			HIY "q" NOR WHT " �뿪��"
			HIY "b" NOR WHT " ǰһҳ��"
			HIC "<num>" NOR WHT " ���� "
			HIC "n" NOR WHT " �У�"
			HIY "n" HIC "<num>" NOR WHT
			"��ʾ���� " HIC "n" NOR WHT " ��)" NOR;
		s_write(show);
		input_to("more_file", file, line + page, total);
	} else
	{
		show += WHT "�Ķ���ϡ�"NOR"\n";
		s_write(show);
	}
}

void start_more_file(string fn)
{
	if (file_size(fn) < 0)
	{
		write("û�� " + fn + " ����ļ��ɹ��Ķ���\n");
		return;
	}
	write("\n");
	more_file("t", fn, 1, file_lines(fn));
}
