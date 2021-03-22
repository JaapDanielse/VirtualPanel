namespace VirtualPanel
{
    partial class InfoForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.InfoLabel = new System.Windows.Forms.Label();
            this.InfoRichTextBox = new System.Windows.Forms.RichTextBox();
            this.SuspendLayout();
            // 
            // InfoLabel
            // 
            this.InfoLabel.BackColor = System.Drawing.Color.Transparent;
            this.InfoLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.InfoLabel.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.InfoLabel.Location = new System.Drawing.Point(12, 11);
            this.InfoLabel.Name = "InfoLabel";
            this.InfoLabel.Size = new System.Drawing.Size(310, 18);
            this.InfoLabel.TabIndex = 0;
            this.InfoLabel.Text = "Virtual Panel ";
            this.InfoLabel.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // InfoRichTextBox
            // 
            this.InfoRichTextBox.BackColor = System.Drawing.SystemColors.ControlLight;
            this.InfoRichTextBox.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.InfoRichTextBox.Location = new System.Drawing.Point(12, 43);
            this.InfoRichTextBox.Name = "InfoRichTextBox";
            this.InfoRichTextBox.Size = new System.Drawing.Size(386, 160);
            this.InfoRichTextBox.TabIndex = 2;
            this.InfoRichTextBox.Text = "";
            this.InfoRichTextBox.LinkClicked += new System.Windows.Forms.LinkClickedEventHandler(this.RichTextBox_LinkClicked);
            // 
            // InfoForm
            // 
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.None;
            this.BackColor = System.Drawing.SystemColors.ControlLight;
            this.ClientSize = new System.Drawing.Size(410, 215);
            this.Controls.Add(this.InfoRichTextBox);
            this.Controls.Add(this.InfoLabel);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "InfoForm";
            this.Text = "Info";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.InfoForm_FormClosing);
            this.Load += new System.EventHandler(this.InfoForm_Load);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Label InfoLabel;
        private System.Windows.Forms.RichTextBox InfoRichTextBox;
    }
}